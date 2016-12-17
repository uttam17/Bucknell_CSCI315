#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "buffer.h"

struct buffer *buffer_create(int max_length) {
	struct buffer *buf = calloc(1, sizeof(struct buffer));
	
	buf->MAX_LENGTH = max_length;
	buf->string = calloc(max_length, sizeof(char));
	buf->print_index = 0;
	buf->print_change = 0;
	buf->index = 0;
	
	return buf;
}

void buffer_empty(struct buffer *buf) {
	int i, len = strlen(buf->string);
	
	while (buffer_increment(buf, 1));
	buffer_print(buf);
	
	for (i = 0; i < len; i++) {
		buffer_remove(buf);
		buffer_print(buf);
	}
}

void buffer_destroy(struct buffer *buf) {
	free(buf);
}

char buffer_get(struct buffer *buf) {
	if (buf->index < buf->MAX_LENGTH) {
		char ret = buf->string[buf->index];
		if (ret) {
			(buf->index)++;
		}
		return ret;
	}
	return 0;
}

int buffer_increment(struct buffer *buf, int i) {
	if (buf->index + i < 0) {
		buf->index = 0;
		return 0;
	} else if (buf->index + i > strlen(buf->string)) {
		buf->index = strlen(buf->string);
		return 0;
	} else {
		buf->index += i;
		return 1;
	}
}

int buffer_insert(struct buffer *buf, const char c) {
	if (buf->index < buf->MAX_LENGTH) {
		char s_temp[buf->MAX_LENGTH];
		strncpy(&(s_temp[0]), &(buf->string[0]), buf->index);
		strncpy(&(s_temp[buf->index++]), &c, 1);
		strcpy(&(s_temp[buf->index]), &(buf->string[buf->index-1]));
		strcpy(&(buf->string[0]), &(s_temp[0]));
		buf->print_change++;
		return 1;
	} else {
		return 0;
	}
}

int buffer_insert_s(struct buffer *buf, char *s) {
	int i;
	for (i = 0; i < strlen(s); i++) {
		if (!buffer_insert(buf, s[i])) {
			return 0;
		}
	}
	return 1;
}

int buffer_remove(struct buffer *buf) {
	if (buf->index > 0) {
		char s_temp[buf->MAX_LENGTH];
		strncpy(&(s_temp[0]), &(buf->string[0]), --(buf->index));
		strcpy(&(s_temp[buf->index]), &(buf->string[buf->index+1]));
		strcpy(&(buf->string[0]), &(s_temp[0]));
		buf->print_change--;
		return 1;
	} else {
		return 0;
	}
}

int buffer_delete(struct buffer *buf) {
	if (buf->index < strlen(buf->string)) {
		char s_temp[buf->MAX_LENGTH];
		strncpy(&(s_temp[0]), &(buf->string[0]), buf->index);
		strcpy(&(s_temp[buf->index]), &(buf->string[buf->index+1]));
		strcpy(&(buf->string[0]), &(s_temp[0]));
		buf->print_change--;
		return 1;
	} else {
		return 0;
	}
}

/**
 * Prints the buffer.
 *
 * @param buf pointer to buffer
 */
void buffer_print(struct buffer *buf) {
	int index = buf->index;
	buf->index = buf->print_index;
	
	while (buffer_increment(buf, -1)) {
		printf("\b");
	}
	
	char temp;
	while ((temp = buffer_get(buf)) != '\0') {
		printf("%c", temp);
	}
	
	int i;
	for (i = 0; i < -buf->print_change; i++) {
		printf(" ");
	}
	while (buf->print_change < 0) {
		printf("\b");
		(buf->print_change)++;
	}
	buf->print_change = 0;
	
	while (buf->index > index) {
		buffer_increment(buf, -1);
		printf("\b");
	}
	
	buf->print_index = index;
}