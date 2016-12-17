/*
 * Copyright (c) 2012 Bucknell University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: L. Felipe Perrone (perrone@bucknell.edu)
 */

#include <stdlib.h>
#include <stdio.h>

#include "cnode.h"
#include "clist.h"

struct clist *
clist_create(int max_length) {
	struct clist *l = calloc(1, sizeof(struct clist));
	l->MAX_LENGTH = max_length;
	return l;
}

void 
clist_destroy(struct clist *l) {
	struct cnode *p = l->front;

	do {
		l->front = l->front->next;
		free(p->command);
		free(p);
		p = l->front;
	} while (l->front != NULL);

	l->front = l->back = NULL;
	l->counter = 0;
}


void 
clist_obliterate(struct clist *l) {
	clist_destroy(l);
	free(l);
}

void 
clist_add_front(struct clist *l, char *com) {
	struct cnode *n = cnode_create(l->MAX_LENGTH);
	cnode_setdata(n, com);

	if (0 == l->counter) {
		l->front = l->back = n;	
		l->counter = 1;
	} else {
		n->next = l->front;
		l->front->prev = n;
		l->front = n;
		(l->counter)++;
	}

#ifdef DEBUG
	printf("counter= %d, %s\n", l->counter, (char *) com);
	printf("front= %s\n", (char *) l->front->command);
	printf("back= %s\n\n", (char *) l->back->command);
#endif /* DEBUG */
}

void 
clist_add_back(struct clist *l, char *com) {
	struct cnode *n = cnode_create(l->MAX_LENGTH);
	n->command = com;

	if (0 == l->counter) {
		l->front = l->back = n;	
		l->counter = 1;
	} else {
		n->prev = l->back;
		l->back->next = n;
		l->back = n;
		(l->counter)++;
	}

#ifdef DEBUG
	printf("counter= %d, %s\n", l->counter, (char *) com);
	printf("front= %s\n", (char *) l->front->command);
	printf("back= %s\n\n", (char *) l->back->command);
#endif /* DEBUG */
}

char *
clist_remove_front(struct clist *l) {
	struct cnode *n = l->front;
	void* com = n->command;

	if (1 == l->counter) {
		l->front = l->back = NULL;
	} else {
		l->front = l->front->next;
		l->front->prev = NULL;
	}

	(l->counter)--;
	free(n);
	return com;
}

char *
clist_remove_back(struct clist *l) {
	struct cnode *n = l->back;
	char *com = n->command;

	if (1 == l->counter) {
		l->front = l->back = NULL;
	} else {
		l->back = l->back->prev;
		l->back->next = NULL;
	}

	(l->counter)--;
	free(n);
	return com;
}

uint32_t 
clist_num_elems(struct clist *l) {
	return l->counter;
}

char *
clist_iter_begin(struct clist *l) {
	char *ret_val = NULL;

	l->iter = l->front;
	if (l->iter != NULL) {
		ret_val = l->iter->command; 
	}

	return ret_val;
}

char *
clist_iter_next(struct clist *l) {
	void *ret_val = NULL;

	if (l->iter != NULL) {
		l->iter = l->iter->next;
		if (l->iter != NULL) {
			ret_val = l->iter->command;
		}
	}

	return ret_val;
}

bool 
clist_iter_has_next(struct clist *l) {
	bool ret_val = false;

	if (l->iter != NULL) {
		ret_val = (l->iter->next != NULL);
	}

#ifdef DEBUG
	if (ret_val) {
		printf("clist_has_next: current is %s\n", (char *) l->iter->command);
		printf("clist_has_next: returning %d\n\n", ret_val);
	}
#endif /* DEBUG */

	return ret_val;
}


char *
clist_iter_end(struct clist *l) {
	void *ret_val = NULL;

	l->iter = l->back;
	if (l->iter != NULL) {
		ret_val = l->iter->command;
	}

	return ret_val;
}

char *
clist_iter_prev(struct clist *l) {
	void *ret_val = NULL;

	if (l->iter != NULL) {
		l->iter = l->iter->prev;
		if (l->iter != NULL) {
			ret_val = l->iter->command;
		}
	}

	return ret_val;
}

bool 
clist_iter_has_prev(struct clist *l) {
	bool ret_val = false;

	if (l->iter != NULL) {
		ret_val = (l->iter->prev != NULL);
	}

	return ret_val;
}

