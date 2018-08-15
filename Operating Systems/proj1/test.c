
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(){

  char str[] ="ls -al ; pwd ; echo hello ";
  char * pch;
  char *argv[64];
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok (str,";");
  while (pch != NULL)
  {
    
    *argv++ = pch;
    pch = strtok(NULL, ";");
  }
  *argv = (char *)'\0';

  return 0;
}
