/*           Blake Kershaw                                              */
/*           COP 4610                                                   */
/*           Assignment 5 (Synchronization)                             */
/*                                                                      */
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

int file_exists(const char * filename);

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

  char yn[3];
  char astr[5], bstr[5];
  char finstr[25];
  int block_number = 1;
  int block_size = 0;


  if(argc < 3 || argc > 3 ){
    fprintf(stderr,"Wrong amount of command line arguments\n");
    exit(1);
  }

  FILE *wp; //declaration for output file descriptor
  
  /* open input file */
  FILE *fp = fopen(argv[1], "rb");

  
  if(fp == NULL){
    fprintf(stderr,"Error opening input file\n");
    exit(1);
  }

  int e = file_exists(argv[2]);
  if( e ){
      printf("The file already exists, do you want to overwrite?(Y/N)\n");
      scanf("%s",yn);
      if( strcmp (yn, "yes") == 0 || strcmp (yn, "y") == 0 || strcmp (yn, "Y") == 0 ){ 
	  wp = fopen(argv[2], "w");
          if(wp == NULL){
              fprintf(stderr,"Error opening output file\n");
              exit(1);
          }
      }
      else{
	printf("Did not overwrite. Exiting\n");
	exit(1);
      }
  }

  if(e == 0){
    /* open output file */    
    wp = fopen(argv[2], "w");
    if(wp == NULL){
      fprintf(stderr,"Error opening output file\n");
      exit(1);
    }
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

    close(fd1[READ_END]);
    close(fd2[WRITE_END]);
    
    while( 1 ){

    block_size = fread(buffer,1,4095,fp);  //scan input file 4095 byte at a time  
   
    if(block_size != 0){
      sprintf(ptr, "%s", buffer ); //write to shared memory
    }

    if(block_size == 0)
      block_number = 0;
    
    sprintf( astr, "%d", block_number);
    sprintf( bstr, "%d", block_size);
    strcpy(finstr, astr);
    strcat(finstr, " ");
    strcat(finstr, bstr);
       
    write(fd1[WRITE_END], finstr, strlen(finstr)+1); // write to the pipe
    //     printf("Parent: writes BN: %s BS:%s\n", astr, bstr);

    
    if( read(fd2[READ_END], read_msg, BUFFER_SIZE) > 0 ){
      sscanf(read_msg, "%d", &var1);
      // printf("Parent: reads value : %d\n", var1);
    }
    else
      break;

    if(var1 == 0)
      break;
    
    ++block_number; 
    
    } //end while

     fclose(fp);
     close(fd1[WRITE_END]);
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

    close(fd1[WRITE_END]);  // close the unused end of the pipe 
    close(fd2[READ_END]);  // close the unused end of the pipe 
    
    while(1){
        
      if(  read(fd1[READ_END], read_msg, BUFFER_SIZE) > 0 ){
	sscanf(read_msg, "%d %d", &var1, &var2);
	//  printf("Child reads value : %d %d\n", var1, var2);
      }
      else
	break;

      if(var1 != 0){
	 sprintf(buffer, "%s", (char *)ptr);
	 fwrite(buffer, 1, var2, wp); ///*write to output file*/
      }
      
      sprintf(write_msg, "%d", var1);
   
      write(fd2[WRITE_END], write_msg, strlen(write_msg)+1);
      //      printf("Child writes value : %d\n", var1);
      if(var1 == 0)
	break;
    }

    //    fwrite('\0', 1, 1, wp);
    fclose(wp);
    close(fd1[READ_END]);
    close(fd2[WRITE_END]);

    /* remove the shared memory segment */
    if (shm_unlink(name) == -1) {
      fprintf(stderr,"Error removing %s\n",name);
      exit(1);
    }    
    
  } //end child process

  return 0;
}

int file_exists(const char * filename)
{
  FILE *file = fopen(filename, "rb");
  if (file == NULL)
    {
        return 0;
    }
    fclose(file);
    return 1;
}

