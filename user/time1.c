#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int start;
  int end;
  int pid;

  if(argc < 2){
    printf("usage: time1 command [args ...]\n");
    exit(1);
  }

  // Record the time before starting the child process.
  start = uptime();

  pid = fork();

  if(pid < 0){
    printf("time1: fork failed\n");
    exit(1);
  }

  if(pid == 0){
    // Child: execute the command being timed.
    exec(argv[1], &argv[1]);

    // exec() only returns if it fails.
    printf("time1: exec failed\n");
    exit(1);
  }

  // Parent: wait for the command to finish.
  wait(0);

  // Record the time after the child has finished.
  end = uptime();

  printf("elapsed time: %d ticks\n", end - start);

  exit(0);
}
