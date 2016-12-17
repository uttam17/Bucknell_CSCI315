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

#ifndef _cnode_H_
#define _cnode_H_

/**
 * Node in a doubly-linked list.
 */
struct cnode {
	struct cnode *next;
	struct cnode *prev;
	char *command;
	int MAX_LENGTH;
};

/**
 * Allocates a new cnode leaving the pointer to data as null.
 *
 * @return pointer to a new cnode
 */
struct cnode *cnode_create(int max_length);

/**
 * Sets the pointer to data with the value passed in.
 *
 * @param n pointer to the dnone
 * @param string pointer to a string
 */
void cnode_setdata(struct cnode *n, char *string);

/**
 * Deallocates a cnode but not the data it points to. The caller must take
 * the responsibility of deallocating the data later on.
 *
 * @param n pointer to the cnode
 * @return pointer to the generic data type associated with node
 */
char *cnode_destroy(struct cnode *n);

#endif /* _cnode_H_ */
