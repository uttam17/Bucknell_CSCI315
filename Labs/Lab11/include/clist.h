#ifndef _clist_H_
#define _clist_H_

#include <stdint.h>
#include <stdbool.h>
#include "cnode.h"

/**
 * Doubly-linked list.
 */
struct clist {
	struct cnode *front;
	struct cnode *back;
	struct cnode *iter;
	int MAX_LENGTH;
	uint32_t counter;
};

/**
 * Allocates new clist dynamically.
 * 
 * @return pointer to the list.
 */
struct clist *clist_create();

/**
 * Deallocates all nodes in a clist and the data they point to, but
 * preserve the list.
 *
 * @param l pointer to the list (non-NULL)
 */
void clist_destroy(struct clist *l);

/**
 * Deallocates all nodes in a clist and the data they point to; deallocate
 * the list itself as well. This is the inverse of clist_create.
 * @param l pointer to the list (non-NULL)
 */
void clist_obliterate(struct clist *l);

/** 
 * Inserts new node in clist before the first node.
 *
 * @param l pointer to the list (non_NULL)
 * @param ptr pointer to generic data to store in new list node
 */
void clist_add_front(struct clist *l, char *str);

/** 
 * Inserts new node in clist after the last node.
 *
 * @param l pointer to the list (non-NULL)
 * @param ptr pointer to generic data to store in new list node
 */
void clist_add_back(struct clist *l, char *str);

/**
 * Remove the first node and return pointer to the data. It is the
 * responsibility of the caller to free the memory pointed by the return
 * value.
 * 
 * @param l pointer to the list (non-NULL)
 * @return pointer to data stored in front node
 */
char *clist_remove_front(struct clist *l);

/**
 * Remove the last node and return pointer to the data. It is the
 * responsibility of the caller to free the memory pointed by the return
 * value.
 * 
 * @param l pointer to the list (non-NULL)
 * @return pointer to data stored in back node
 */
char *clist_remove_back(struct clist *l);

/**
 * Returns the number of elements in the list (nodes).
 *
 * @param l pointer to the list (non-NULL)
 */
uint32_t clist_num_elems(struct clist *l);

/**
 * Initialize iterator for traversing a clist forwards.
 */
char *clist_iter_begin(struct clist *l);

/** 
 * Returns current item and advances iterator to next item in list.
 */
char *clist_iter_next(struct clist *l);

/**
 * Check if iterator has reached the end of the list.
 */
bool clist_iter_has_next(struct clist *l);

/**
 * Initialize iterator for traversing a clist backwards.
 */
char *clist_iter_end(struct clist *l);

/** 
 * Returns current item and advances iterator to previous item in list.
 */
char *clist_iter_prev(struct clist *l);

/**
 * Check if iterator has reached the start of the list.
 */
bool clist_iter_has_prev(struct clist *l);

#endif /* _clist_H_ */
