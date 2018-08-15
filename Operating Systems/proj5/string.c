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
  int var1 = -1;
  int var2;
  int child_block = 1;
  
  char astr[5], bstr[5];
  char finstr[25];
  int block_number = 1;
  int block_size = 0;
 
  while(1){ 
  sprintf(write_msg, "%d", block_number);
  
  sscanf(write_msg, "%d", &var1);
  printf("CHILD: %d\n",var1);

  ++block_number;
  if (block_number == 11)
    break;
}



  return 0;
}
