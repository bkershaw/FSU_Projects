/*                       compile with:                                  */
/* gcc -std=c99 -Wall -Wextra -D_XOPEN_SOURCE=700 -o trans trans.c -lrt */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define READ_END      0
#define WRITE_END     1
#define BUFFER_SIZE          25

int main(){

  const int SIZE = 4096;
  const char *name = "bk15b_cop4610";
  int shm_fd;
  void *ptr;

  char buffer[4096];
  char read_msg[BUFFER_SIZE];
  char write_msg[BUFFER_SIZE];
  char read_msg_c[BUFFER_SIZE];
  char write_msg_c[BUFFER_SIZE];

  int var1 = -1;
  int var2;
  int child_block = 1;
  
  char astr[5], bstr[5];
  char finstr[25];
  int block_number = 1;
  int block_size = 0;

  
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

    while(block_number){
      close(fd1[READ_END]);  // close the read end of parent
      close(fd2[WRITE_END]); // close write end of child
    
      sprintf(write_msg, "%d", block_number);
      
      write(fd1[WRITE_END], write_msg, strlen(write_msg)+1); // write to the pipe  
      
      read(fd2[READ_END], read_msg, BUFFER_SIZE); //read from child
      sscanf(read_msg, "%d", &var2);

      ++block_number;

      if (block_number = 11)        
        break;      
    } //end while

    if( var2 == 10)
      close(fd1[WRITE_END]); // close write end of parent    
    
    printf("EXITING PARENT bn:%d var2:%d\n", block_number, var2); 
  }//end parent

  /* child process */
  else { 
    
    while(1){
      close(fd1[WRITE_END]); // close write end of parent
      close(fd2[READ_END]);  // close read end of child

      read(fd1[READ_END], read_msg_c, BUFFER_SIZE); //read from parent
      
      printf("%s\n",read_msg_c);

      sscanf(read_msg_c, "%d", &var1);
      printf("CHILD: %d\n",var1);

      sprintf(write_msg_c, "%d", var1);
   
      write(fd2[WRITE_END], write_msg_c, strlen(write_msg_c)+1 ); // write out to parent

      if(var1 == 10)
         break;      
      
     }

    close(fd2[WRITE_END]);
    printf("EXITING CHILD var1:%d\n", var1); 

  } //end child process

  return 0;
}
