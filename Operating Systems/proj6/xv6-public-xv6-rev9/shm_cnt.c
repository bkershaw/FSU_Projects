/*  Test Harness for Shared Memory Implmentation  */
/*   ( Implmentation can be found in vm.c)        */
/*  Blake Kershaw                                 */
/*  COP4610                                       */
/*  Assignment 6                                  */

#include "types.h"
#include "user.h"
#include "stat.h"
#include "uspinlock.h"

 struct shm_cnt{
      struct uspinlock lock;
      volatile int cnt;
    }; 

int main(){
  int pid = fork();
  if (pid < 0) {
    printf(1,"Fork failed\n");
    exit();
  }

  // Parent Process
  if (pid > 0){
  
   struct shm_cnt *pbase;
   pbase = (struct shm_cnt *) shm_open(0xbeefbeef);

   int p;
   uinitlock(&pbase->lock);

   for(p = 0; p < 10000; p++){
     uacquire(&pbase->lock);   
     pbase->cnt += 1;
     urelease(&pbase->lock);
   }
 
   wait();

  //the following should print 200000
  printf(1,"pbase->cnt value: %d\n", pbase->cnt);

  shm_close(0xbeefbeef);
    
   exit();
  } //end parent proccess

  // Child Process
  else{
    
    sleep(1); 
    
    struct shm_cnt *cbase;
    cbase = (struct shm_cnt *) shm_open(0xbeefbeef); 
    int c;

    for(c = 0; c < 10000; c++){
     uacquire(&cbase->lock);
     cbase->cnt +=1;
     urelease(&cbase->lock);
    }

    shm_close(0xbeefbeef);      
    
    exit();
  } //end child process

  return 0;
}
