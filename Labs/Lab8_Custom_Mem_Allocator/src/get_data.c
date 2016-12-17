#include <stdlib.h>
#include <stdio.h>
#include "dnode.h"
#include "dlist.h"
#include "allocator.h"

int main() {
  int sample_num = 500;
  int request_num = 30;
  double first_fit[sample_num];
  double best_fit[sample_num];
  double worst_fit[sample_num];

  int seed = 0;
  int i = 0;
  for (i = 0; i < sample_num; i++) {
    first_fit[i] = frag_eval(0, seed, request_num);
    seed++;
  }

  for (i = 0; i < sample_num; i++) {
    best_fit[i] = frag_eval(1, seed, request_num);
    seed++;
  }

  for (i = 0; i < sample_num; i++) {
    worst_fit[i] = frag_eval(2, seed, request_num);
    seed++;
  }

  FILE *f = fopen("results.txt", "w");
  //Taken from stack question about saving data to txt file
  for (i = 0; i < sample_num; i++) {
    fprintf(f, "%lf %lf %lf\n", first_fit[i], best_fit[i], worst_fit[i]);
  } 
  fclose(f);
  return 0;
}

//Placed frag_eval function here to make running get_data easier
int frag_eval(int policy, int seed, int num_requests) {
  allocator_init(10000);
  int x = 0;
  void **request_array[num_requests];
  srand(seed);
  int s = 0;

  for(x=0; x < num_requests; x++) {    
    s = randr(100,1000);
    request_array[x] = allocate(request_arrayolicy, s);
  }
  
  int y = 0;
  for(y=0; y < num_requests; y++) {    
    if (request_array[y] != NULL) deallocate(request_array[y]);
  }
  return average_frag();
}

//Adapted from stack overflow solution for generating random values within range quickly
int randr(unsigned int min, unsigned int max){
  double scaled = (double)rand()/RAND_MAX;
  return (max - min +1)*scaled + min;
}