#include <string.h>
#include <stdio.h>
#include "buffer.h"

int main(int argc, char *argv[]) {
	struct buffer *buf = buffer_create(100);
	
	char * string = "Hello World";
	int i;
	
	fflush(stdout);
	sleep(2);
	
	for (i = 0; i < strlen(string); i++) {
		buffer_insert(buf, string[i]);
	}
	buffer_print(buf);
	fflush(stdout);
	sleep(2);
	
	for (i = 0; i < 5; i++) {
		buffer_remove(buf);
	}
	buffer_print(buf);
	fflush(stdout);
	sleep(2);
	
	string = "Sam";
	for (i = 0; i < strlen(string); i++) {
		buffer_insert(buf, string[i]);
	}
	buffer_print(buf);
	fflush(stdout);
	sleep(2);
	
	char c = 'H';
	
	buffer_increment(buf, -2);
	buffer_print(buf);
	fflush(stdout);
	sleep(2);
	
	buffer_remove(buf);
	buffer_insert(buf, c);
	buffer_print(buf);
	fflush(stdout);
	sleep(2);
	
	buffer_increment(buf, 2);
	buffer_print(buf);
	fflush(stdout);
	sleep(2);
	
	buffer_destroy(buf);
	return 0;
}