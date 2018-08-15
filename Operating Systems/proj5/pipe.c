#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ  0
#define WRITE 1

int main(void)
{
  pid_t pid;
  //open two pipes, one for each direction
  int fd1[2];
  int fd2[2];

  /* create the pipe */
  if (pipe(fd1) == -1 || pipe(fd2) == -1) {
    fprintf(stderr,"Pipe failed");
    return 1;
  }

  /* now fork a child process */
  pid = fork();

  if (pid < 0) {
    fprintf(stderr, "Fork failed");
    return 1;
  }

  if(pid > 0){
  int parentVal = 0;
  close(fd1[READ]);      // The parent is not going to read from the first
                              // pipe.
  // Close the read end of the pipe.
  close(fd2[WRITE]);    // The parent is not going to write to the second
                              // pipe.
  // Close the write end of the pipe.
  while(1) { 

    parentVal++;
    write(fd1[WRITE],&parentVal,sizeof(parentVal));
    printf("Parent: writes value : %d\n", parentVal);
     
    // If the chld closes the write end of the second pipe,
    // break out of the loop.
    if ( read(fd2[READ],&parentVal,sizeof(parentVal)) > 0 )
    {
      printf("Parent: reads value : %d\n", parentVal);
    }
    else
    {
      break;
    }

    if( parentVal == 10)
      break;

  }

  close(fd1[WRITE]);    // Close the write end of the first pipe
  close(fd2[READ]);    // Close the read end of the second pipe
}
 else { /* child process */
   int childVal = 0;
   close(fd1[WRITE]);    // The child is not going to write to the first
                              // pipe.
   // Close the write end of the pipe.
   close(fd2[READ]);    // The child is not going to read from the second
                              // pipe.
   // Close the read end of the pipe.
   while(1) {
     
     // If the parent closes the write end of the first pipe,
     // break out of the loop.
     if ( read(fd1[READ],&childVal,sizeof(childVal)) > 0 )
     {
       printf("child: read value : %d\n", childVal);
     }
     else
     {
       break;
     }    

     childVal++;
     write(fd2[WRITE],&childVal,sizeof(childVal));
     printf("child: write value : %d\n",childVal);
     if(childVal == 10)
       break;


   }
   close(fd1[READ]);     // Close the read end of the first pipe
   close(fd2[WRITE]);   // Close the write end of the second pipe
 }
}

 
