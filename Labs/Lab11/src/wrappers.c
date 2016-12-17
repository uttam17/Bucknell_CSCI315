#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "wrappers.h"

int Fork() {
  int retval;
  if ((retval = fork()) == ERROR) {
    perror("Fork Error");
  }
  return retval;
}

pid_t Wait(int *status) {
  pid_t retval;
  if ((retval = wait(status)) == ERROR) {
    perror("Wait Error");
  }
  return retval;
}

int Execv(const char *path, char *const argv[]) {
  int retval;
  if ((retval = execv(path, argv)) == ERROR) {
	  perror("Execv Error");
  }
  return retval;
}