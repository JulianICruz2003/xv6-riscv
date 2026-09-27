#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int start;
  int end;
  int elapsed;
  int percent;
  int pid;
  int status;
  struct rusage usage;

  if(argc < 2){
    printf("usage: time command [args ...]\n");
    exit(1);
  }

  // Record elapsed-time starting point.
  start = uptime();

  pid = fork();

  if(pid < 0){
    printf("time: fork failed\n");
    exit(1);
  }

  if(pid == 0){
    // Child executes the requested command.
    exec(argv[1], &argv[1]);

    // exec only returns if it failed.
    printf("time: exec failed\n");
    exit(1);
  }

  // Parent waits for the child and receives its CPU usage.
  if(wait2(&status, &usage) < 0){
    printf("time: wait2 failed\n");
    exit(1);
  }

  end = uptime();
  elapsed = end - start;

  // Avoid division by zero for extremely short commands.
  if(elapsed > 0)
    percent = (usage.cputime * 100) / elapsed;
  else
    percent = 0;

  printf("elapsed time: %d ticks, cpu time: %d ticks, %d%% CPU\n",
         elapsed, usage.cputime, percent);

  exit(0);
}
