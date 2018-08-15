#include "types.h"
#include "stat.h"
#include "user.h"



int
main(int argc, char *argv[])
{

/*  if(argc <= 1){
    printf(1,"Who ar you?\n");
    exit();
  }
*/
  int pid = getpid();
  
  printf(1,"Hello Xv6, PID:%d\n",pid);

  exit();
}
