#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlist.h"
#include "allocator.h"
#include "dnode.h"
struct dlist *free_list;
struct dlist *allocated_list;
int allocator_size;
int fragment_amt;

int allocator_init(size_t size){
	fragment_amt = 0;
	allocator_size = size;
	free_list = dlist_create();
	allocated_list = dlist_create();
	int* data;
	if((data = malloc(size))  == NULL){
		return -1;
	}
	struct dnode* n = dnode_create();
	dnode_setdata(n, data, size); 
	dlist_add_front(free_list, n);
	
	/*printf("Free List Before Allocation\n");
	printList(free_list);
	printf("\n");

	printf("Allocated List Before Allocation\n");
	printList(allocated_list);*/

	return 0;
}

void *allocate (int policy, size_t size){
	if(policy == 0){
		return first_fit(size);
	} 
	else if(policy == 1){
		return best_fit(size);
	} 
	else if(policy == 2){
		return worst_fit(size);
	} 
	return NULL;
}

void *first_fit (size_t size){
  struct dnode* temp_node = free_list->front;

  while(temp_node != NULL){
  	if (temp_node->size >= (int) size){
  		struct dnode* node_add = dnode_create();

		dnode_setdata(node_add, temp_node->data, (int) size);
		/*printf("new size: %d\n", (int) node_add->size);
		printf("first node size: %d\n", (int) temp_node->size);*/

		dlist_add_front(allocated_list,node_add);
/*		printf("After First Fit Add\n");
*/
		temp_node->size = (int) temp_node->size - size;
/*		printf("temp node size: %d\n", (int) temp_node->size);
*/
		temp_node->data += size;
		free_list->front = temp_node;
			fragment_amt +=1;

/*		printf("\n");
*/
		/*//Printing Both Lists for Visual Verification
		printf("Free List\n");
		printList(free_list);
		printf("\n");
		printf("Allocated List\n");
		printList(allocated_list);
		printf("\n");*/
                                
  		if(temp_node->size ==0){
  			dlist_find_remove(free_list, temp_node);
  			free(temp_node);
  		}
		return node_add;
  	}	

  	temp_node = temp_node->next;
  } 
   return NULL;
}

void *best_fit (size_t size){
  struct dnode* temp_node = free_list->front;
  struct dnode* best_fit_node = dnode_create();
  best_fit_node = temp_node;
  while(temp_node != NULL){
  	if(temp_node->size > best_fit_node->size){
  		best_fit_node = temp_node;
  	}
  	temp_node = temp_node->next;
  }

  if(best_fit_node->size <size){
  	return NULL;
  }
  		struct dnode* node_add = dnode_create();
		dnode_setdata(node_add, best_fit_node->data, (int) size);
		dlist_add_front(allocated_list,node_add);
		/*printf("\n");

		printf("After Best Fit Add\n");*/
		best_fit_node->size = (int) best_fit_node->size - size;

		best_fit_node->data += size;
		free_list->front = best_fit_node;
		fragment_amt += 1;

		/*printf("\n");

		//Printing Both Lists for Visual Verification
		printf("Free List\n");
		printList(free_list);
		printf("\n");
		printf("Allocated List\n");
		printList(allocated_list);
		printf("\n");*/
                                
  		if(best_fit_node->size ==0){
  			dlist_find_remove(free_list, best_fit_node);
  			free(best_fit_node);
  		}
		return node_add;
  	}	

void *worst_fit (size_t size){
	struct dnode* temp_node = free_list->front;
  struct dnode* worst_fit_node = dnode_create();
  worst_fit_node = temp_node;
  while(temp_node != NULL){
  if ((temp_node->size >= size) && (temp_node->size < worst_fit_node->size)){
			worst_fit_node = temp_node;
		}
		temp_node=temp_node->next;
	}

	if(worst_fit_node->size<size){
		return NULL;
	}
  		struct dnode* node_add = dnode_create();
		dnode_setdata(node_add, worst_fit_node->data, (int) size);
		dlist_add_front(allocated_list,node_add);

		/*printf("\n");
		printf("After Worst Fit Add\n");*/
		worst_fit_node->size = (int) worst_fit_node->size - size;
		worst_fit_node->data += size;
		free_list->front = worst_fit_node;
		fragment_amt +=1;

		/*printf("\n");

		//Printing Both Lists for Visual Verification
		printf("Free List\n");
		printList(free_list);
		printf("\n");
		printf("Allocated List\n");
		printList(allocated_list);
		printf("\n");*/
                                
  		if(worst_fit_node->size ==0){
  			dlist_find_remove(free_list, worst_fit_node);
  			free(worst_fit_node);
  		}
		return node_add;
  	}	

int deallocate(void *ptr){
	struct dnode *temp_node = dnode_create();
	temp_node = allocated_list->front;
	size_t size;
	struct dnode *ptr_node = dnode_create();
	ptr_node = ptr;
	while(temp_node!= NULL){
		if (temp_node->size == ptr_node->size){
			/*printf("Pointer is: %d\n", ptr_node->size);
			printf("temp is: %d\n", temp_node->size);
			printf("front is: %d\n", free_list->front->size);*/

			size = temp_node->size;
			free_list->front->size 	= (int) ptr_node->size;

			dlist_find_remove(allocated_list, temp_node);
			free(temp_node);
			(allocated_list->counter)--;
			/*//Printing Both Lists for Visual Verification
			printf("Free List\n");
			printList(free_list);
			printf("\n");
			printf("Allocated List\n");
			printList(allocated_list);
			printf("\n");*/
			return 0;
			}
		else{
			temp_node = temp_node->next;				
		}
	}
	return -1;
}

int printList(struct dlist *l) {
  struct dnode* temp_node = l -> front;
  while (temp_node != NULL) {
    printf("%d -> ", temp_node -> size);
    temp_node = temp_node -> next;
  }
  printf("\n");
  return 0;
}

double average_frag(){
	return (double) allocator_size / (double) fragment_amt;
}
