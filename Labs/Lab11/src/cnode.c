#include <stdlib.h>
#include <string.h>
#include "cnode.h"

struct cnode *cnode_create(int max_length) {
	struct cnode *n = calloc(1, sizeof(struct cnode));
	n->MAX_LENGTH = max_length;
	n->command = calloc(max_length, sizeof(char));
	return n;
}

void cnode_setdata(struct cnode *n, char *str) {
	strcpy(n->command,str);
}

char *cnode_destroy(struct cnode *n) {
	char *str = n->command;
	free(n);
	return str;
}
