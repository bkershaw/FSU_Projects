#include "types.h"
#include "user.h"
#include "stat.h"

#define MAX_CHILDREN 4
#define LOWEST_PRIO 200 // The higher the value, the lower the priority
#define HIGHEST_PRIO 0

void sameWorkDifferentPrio();

int main(int argc, char *argv[])
{
  // Give the parent high priority so it can spawn all children without interruption
  setpriority(HIGHEST_PRIO);
	
  printf(1, "Now testing same work with different priorities\n");
  sameWorkDifferentPrio();
	
  exit();
}


// This should only be called in a parent process
void waitOnChildren(int num_children)
{
  int i;
  for(i = 0; i < num_children; ++i)
    wait();
}

void sameWorkDifferentPrio()
{
  int pid;
  int i;
  int successful_forks = 0;
	
  for(i = 0; i < MAX_CHILDREN; i++){
    pid = fork();
    if(pid < 0)
      printf(1, "Fork failed.\n");
    else if(pid == 0) {
      setpriority(200-i);
      printf(1, "SPAWNED PROCESS %d WITH PRIORITY %d\n", i, 200 -i);
      int j;
      for(j = 0; j < 1000000; j++);
      printf(1, "EXITING PROCESS %d\n", i);
      exit();
    }
    else
      ++successful_forks;	
  }
	
  waitOnChildren(successful_forks);
}
