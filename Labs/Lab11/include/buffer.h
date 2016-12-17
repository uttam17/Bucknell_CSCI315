/**
 * Doubly-linked list.
 */
struct buffer {
	char *string;
	int MAX_LENGTH;
	int index;
	int print_index;
	int print_change;
};

/**
 * Allocates new dlist dynamically.
 * 
 * @param max_length is the largest the buffer can grow to.
 * @return pointer to the list.
 */
struct buffer *buffer_create(int max_length);

/**
 * Empties the string
 * @param buf pointer to the list (non-NULL)
 */
void buffer_empty(struct buffer *buf);

/**
 * Deallocates all nodes in a dlist and the data they point to; deallocate
 * the list itself as well. This is the inverse of dlist_create.
 * @param buf pointer to the list (non-NULL)
 */
void buffer_destroy(struct buffer *buf);

/** 
 * Gets node in dlist at the location
 * nodes over.
 *
 * @param buf pointer to the list (non-NULL)
 * @return character at index.
 */
char buffer_get(struct buffer *buf);

/**
 * Increments the index by i
 *
 * @param i increment
 * @return success status
 */
int buffer_increment(struct buffer *buf, int i);
 
/** 
 * Inserts new character at index.
 *
 * @param buf pointer to the list (non-NULL)
 * @param c char for character
 * @return success status
 */
int buffer_insert(struct buffer *buf, const char c);

/** 
 * Inserts new character at index.
 *
 * @param buf pointer to the list (non-NULL)
 * @param c char for character
 * @return success status
 */
int buffer_insert_s(struct buffer *buf, char *c);

/** 
 * Removes character at index.
 *
 * @param buf pointer to the list (non-NULL)
 * @param c char for character
 * @return success status
 */
int buffer_remove(struct buffer *buf);

/** 
 * Removes character at index - 1.
 *
 * @param buf pointer to the list (non-NULL)
 * @param c char for character
 * @return success status
 */
int buffer_delete(struct buffer *buf);

/**
 * Prints the buffer.
 *
 * @param buf pointer to buffer
 */
void buffer_print(struct buffer *buf);

