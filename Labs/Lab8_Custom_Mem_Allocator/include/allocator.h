#include <stddef.h>
int allocator_init(size_t size); 

void *allocate(int policy, size_t size); 

int deallocate(void *ptr); 

void *first_fit(size_t size);

void *best_fit(size_t size);

void *worst_fit(size_t size);

double average_frag();

