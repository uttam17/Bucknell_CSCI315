#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]){
  FILE *file;
  file = fopen("channel.txt","a");
  fwrite(argv[1],sizeof(char),strlen(argv[1]),file);
  fclose(file);
  return 0;
}