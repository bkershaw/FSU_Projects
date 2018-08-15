/*                       compile with:                                  */
/* gcc -std=c99 -Wall -Wextra -D_XOPEN_SOURCE=700 -o trans trans.c -lrt */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <sys/wait.h>

#define READ_END      0
#define WRITE_END     1
#define BUFFER_SIZE          25

int main(int argc, char *argv[]){

  const int SIZE = 4096;
  const char *name = "bk15b_cop4610";
  int shm_fd;
  void *ptr;

  char buffer[4096];
  char read_msg[BUFFER_SIZE];
  char write_msg[BUFFER_SIZE];
  int var1 = -1;
  int var2;
  int child_block = 1;
  
  char astr[5], bstr[5];
  char finstr[25];
  int block_number = 1;
  int block_size = 0;


  if(argc < 3 || argc > 3 ){
    fprintf(stderr,"Wrong amount of command line arguments\n");
    exit(1);
  }

  /* open input file */
  FILE *fp = fopen(argv[1], "rb");

  if(fp == NULL){
    fprintf(stderr,"Error opening input file\n");
    exit(1);
  }

  /* open output file */
  FILE *wp = fopen(argv[2], "w");

  if(wp == NULL){
    fprintf(stderr,"Error opening output file\n");
    exit(1);
  }
  
  int fd1[2]; //parent pipe
  int fd2[2]; //child pipe
  
  /* create the parent pipe*/
  if (pipe(fd1) == -1){
     fprintf(stderr,"Parent Pipe Failed\n");
     exit(1);
 }     
 
 /* create the child pipe*/
  if (pipe(fd2) == -1){
     fprintf(stderr,"Parent Pipe Failed\n");
     exit(1);
 }     

  pid_t pid = fork();
  if (pid < 0) {
    fprintf(stderr, "Fork failed");
    exit(1);
  }

  if (pid > 0) {  /* parent process */
    
    /* open the shared memory segment */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    
    /* configure the size of the shared memory segment */
    ftruncate(shm_fd,SIZE);

    /* now map the shared memory segment in the address space of the process  */
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED){
      fprintf(stderr, "Parent: Map failed %d %s\n", block_number, strerror(errno));
      exit(1);
    }

    fseek(fp, SEEK_SET, 0);

    /* Scan input file 4096Byte at a time  */
    block_size = fread(buffer,1,4096,fp);
    while( block_size ){

      /* Write to the shared memory  */
      sprintf(ptr, "%s", buffer);
      ptr += strlen(buffer);

      sprintf( astr, "%d", block_number);
      sprintf( bstr, "%d", block_size);
      strcpy(finstr, astr);
      strcat(finstr, " ");
      strcat(finstr, bstr);
   
    /* close the unused end of the pipe */
    close(fd1[READ_END]);

    /* write to the pipe */
    write(fd1[WRITE_END], finstr, strlen(finstr)+1); 

    /* close the write end of the pipe */
    close(fd1[WRITE_END]);

    wait(NULL);

    /* close the unused end of the child pipe */
      close(fd2[WRITE_END]);

      /* read from the child pipe */
      read(fd2[READ_END], read_msg, BUFFER_SIZE);
    
      sscanf(read_msg, "%d", &var1);    

      /* close the read end of the pipe */
      close(fd2[READ_END]);
    

    ++block_number;
    block_size = fread(buffer,1,4096,fp);  
    } //end while

     fclose(fp);

    block_number = 0;
    //block_size = 0;

    sprintf( astr, "%d", block_number);
    sprintf( bstr, "%d", block_size);
    strcpy(finstr, astr);
    strcat(finstr, " ");
    strcat(finstr, bstr);

    /* close the unused end of the pipe */
    close(fd1[READ_END]);
   
    /* write to the pipe */
    write(fd1[WRITE_END], finstr, strlen(finstr)+1); 

    /* close the write end of the pipe */
    close(fd1[WRITE_END]);

    wait(NULL);
    
      /* close the unused end of the child pipe */
      close(fd2[WRITE_END]);

      /* read from the child pipe */
      read(fd2[READ_END], read_msg, BUFFER_SIZE);
    
      sscanf(read_msg, "%d", &var1);    

      /* close the read end of the pipe */
      close(fd2[READ_END]);
      }//end parent

  /* child process */
  else { 

     /* open the shared memory segment */
    shm_fd = shm_open(name, O_RDONLY, 0666);
    if (shm_fd == -1) {
      fprintf(stderr,"shared memory failed\n");
      exit(1);
    }

    /* now map the shared memory segment in the address space of the process */
    ptr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
      printf("Child: Map failed\n");
      exit(1);
    }  

    
    /* close the unused end of the pipe */
    close(fd1[WRITE_END]);

    /* read from the pipe */
    read(fd1[READ_END], read_msg, BUFFER_SIZE);
    
    sscanf(read_msg, "%d %d", &var1, &var2);
    
    /* close the read end of the pipe */
    close(fd1[READ_END]);
    
    /*read from shared memory*/     
    sprintf(buffer, "%s", (char *)ptr);
    ptr += var2; //increment ptr based on block_size sent from parent
    
    /*write to output file*/
    fwrite(buffer, 1, strlen(buffer)+1, wp);

    /* close the unused end of the pipe */
    close(fd2[READ_END]);  

    sprintf(write_msg, "%d", var1);
   
    /*  write to the pipe */
    write(fd2[WRITE_END], write_msg, strlen(write_msg)+1); 

    /* close the write end of the pipe */
    close(fd2[WRITE_END]);

    /* IF PARENT SENDS BLOCKSIZE 0 CLOSE AND UNLINK*/
    if( var1 == 0 ){
      fclose(wp);

      /* remove the shared memory segment */
      if (shm_unlink(name) == -1) {
        fprintf(stderr,"Error removing %s\n",name);
        exit(1);
      }    
    }
  } //end child process

  return 0;
}
