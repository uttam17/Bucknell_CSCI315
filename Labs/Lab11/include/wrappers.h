#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#ifndef WRAPPERS_H
#define WRAPPERS_H

#define ERROR -1
#define LINE_LEN 1024

int Fork();
pid_t Wait(int *status);
int Execv(const char *path, char *const argv[]);

#endif 