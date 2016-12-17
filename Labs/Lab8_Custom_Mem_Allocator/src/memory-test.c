#include <stdlib.h>
#include <stdio.h>
#include "dnode.h"
#include "dlist.h"
#include "allocator.h"


int main() {
  printf("\n");

  printf("Create allocator with 1000 size\n");
  allocator_init(1000, 1);
  printf("Allocate memory segment 1 of 500 bytes\n");
  void* mem_seg1 = allocate(500);
  printf("\n");
  
  printf("Allocate memory segment 2 of 400 bytes\n");
  void* mem_seg2 = allocate(400);
  if(mem_seg2 == NULL){
    printf("Allocation successful");
  }
  printf("Allocate memory segment 3 of 200 bytes\n");
  void* mem_seg3 = allocate(200);
  printf("This should not work as there is only 100 bytes of space left\n");
  printf("\n");

  printf("Allocate memory segment 4 of 100 bytes\n");
  void* mem_seg4 = allocate(100);
  printf("\n");

  

  int a = deallocate(mem_seg1);
  printf("Deallocate memory segment 1\n");
  deallocate(mem_seg2);
  printf("Deallocate memory segment 2\n");
  deallocate(mem_seg4);
  printf("Deallocate memory segment 4\n");

}

