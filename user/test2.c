#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  printf("test2 started, pid = %d\n", getpid());

  for (volatile int i = 0; i < 100000000; i++) {
  }

  printf("test2 finished\n");
  exit(0);
}
