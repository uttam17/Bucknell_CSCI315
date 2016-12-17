 #include <stdio.h>
 #include <stdlib.h>
 #include <errno.h>
 #include <semaphore.h>
 #define MAX 100
 #define SNAME "mysem"
 
 int main(int argc, char* argv[]){
   while(1){
     char buff[MAX];
     FILE *file;
     int numBytes;
     file = fopen("channel.txt", "r");
     numBytes = fread(buff, sizeof(buff), 1, file);
     printf("reciever [msg arrival]: '%s'", &buff[numBytes]);
   }
 }