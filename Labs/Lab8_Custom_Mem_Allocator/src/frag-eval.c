#include <stdlib.h>
#include <stdio.h>
#include "dnode.h"
#include "dlist.h"
#include "allocator.h"
int main(int argc, char* argv[]) {

  if (argc != 4) {
    printf("frag-eval [algorithm] [seed] [num_requests]\n");
    return 0;
  }
  
  int policy = atoi(argv[1]);
  int seed = atoi(argv[2]);
  int num_requests = atoi(argv[3]);
  allocator_init(10000);

  srand(seed);
  int x = 0;
  void **p[num_requests];
  int s = 0;

  for(x=0; x < num_requests; x++) {    
    s = randr(100,1000);
    p[x] = allocate(policy, s);
  }
  
  int y = 0;
  for(y=0; y < num_requests; y++) {    
    if (p[y] != NULL) deallocate(p[y]);
  }
  printf("Average fragmentation: %lf\n", average_frag());
}

//Adapted from stack overflow solution for generating random values within range quickly
int randr(unsigned int min, unsigned int max){
  double scaled = (double)rand()/RAND_MAX;
  return (max - min +1)*scaled + min;
}