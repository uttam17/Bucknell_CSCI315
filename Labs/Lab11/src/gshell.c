#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>

#include "wrappers.h"
#include "buffer.h"
#include "clist.h"

#define BACKSPACE 8
#define NEWLINE 10
#define MAX 126
#define MIN 31
#define SPECIAL_KEY 27
#define UP 65
#define DOWN 66
#define RIGHT 67
#define LEFT 68
#define ARROW 91
#define DEL2 51
#define DEL3 126

/**
 * Reads from keypress, doesn't echo 
 * 
 * @author http://stackoverflow.com/questions/3276546/how-to-implement-getch-function-of-c-in-linux
 * @return the int representing the character entered
 */
int getch(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	
    return ch;
}

/**
 * Gets the number of words in a string
 * 
 * @param buffer the string of words
 * @return the number of lines
 */
int get_line_count(char *buffer){
    int line_count = 0;
	char *tok_string = calloc(strlen(buffer), sizeof(char));
	strcpy(tok_string, buffer);
	
	char *line = strtok(tok_string, ";");
	
    while (line) {
		line_count++;
		line = strtok(NULL, ";");
	}
	
    return line_count;
}

/**
 * Gets the number of words and lines in a string
 * 
 * @param buffer the string of words
 */
int *get_word_count(char *buffer, int *line_count){
    int l = 0;
	*line_count = get_line_count(buffer);
    int *word_count = calloc(*line_count, sizeof(int));
	char *save_ptr1 = calloc(LINE_LEN, sizeof(char)), 
		 *save_ptr2 = calloc(LINE_LEN, sizeof(char));
	
	char *line = strtok_r(buffer, ";", &save_ptr1);
	while (line) {
		char *word = strtok_r(line, " ", &save_ptr2);
		while (word) {
			word = strtok_r(NULL, " ", &save_ptr2);
			word_count[l]++;
		}
		line = strtok_r(NULL, ";", &save_ptr1);
		word_count[l++];
	}
    
    return word_count;
}

/**
 * Sends a beep to the user.
 */
void beep() {
	printf("\a");
}

/**
 * Gets a command from the user input and keeps a history of the previous commands
 *
 * @param com_buf 		struct clist *
 * @param prev_newtab	pointer to prev_newtab counter
 * @return pointer 		the command entered
 */
char *get_command(struct clist *com_buf, int *prev_newtab) {
	struct buffer *buf = buffer_create(LINE_LEN);
	char *new_line = calloc(LINE_LEN, sizeof(char));
	int clist_i = -1;
	char c;
	
	fflush(stdout);
	fflush(stdin);
	
	while ((c = getch()) != NEWLINE) {
		if (c == '\t') {
			(*prev_newtab)++;
		} else if (c == BACKSPACE) {
			if (!buffer_remove(buf)) {
				beep();
			}
		} else if (c >= MIN && c <= MAX) {
			buffer_insert(buf, c);
		} else if (c == SPECIAL_KEY) {
			char c1 = getch();
			char c2 = getch();
			
			if (c1 == ARROW) {
				if (c2 == LEFT) {
					if (!buffer_increment(buf, -1)) {
						beep();
					}
				} else if (c2 == RIGHT) {
					if (!buffer_increment(buf, 1)) {
						beep();
					}
				} else if (c2 == UP) {
					if (clist_i == -1 && clist_num_elems(com_buf) > 0) {
						strcpy(new_line, buf->string);
						buffer_empty(buf);
						buffer_insert_s(buf, clist_iter_begin(com_buf));
						clist_i = 0;
					} else if (clist_num_elems(com_buf) > 0 && clist_iter_has_next(com_buf)) {
						buffer_empty(buf);
						buffer_insert_s(buf, clist_iter_next(com_buf));
						clist_i++;
					} else {
						beep();
					}
				} else if (c2 == DOWN) {
					if (clist_i > 0 && clist_iter_has_prev(com_buf)) {
						buffer_empty(buf);
						buffer_insert_s(buf, clist_iter_prev(com_buf));
						clist_i--;
					} else if (clist_i == 0) {
						buffer_empty(buf);
						buffer_insert_s(buf, new_line);
						clist_i = -1;
					} else {
						beep();
					}
				} else {
					int c3 = getch();
					if (c2 == DEL2 && c3 == DEL3) {
						if (!buffer_delete(buf)) {
							beep();
						}
					}
				}
			}
		}
		buffer_print(buf);
		
		if (*prev_newtab == 2) {
			break;
		}
	}
	
	printf("\n");
	return buf->string;
}

/**
 * Handles the calculator functionality.
 *
 * @param num1 float
 * @param num2 float
 * @param operator char * representing the operation
 */
int calculator(float num1, float num2, char operator) {
	float ans;

	switch (operator) {
		case '+': 
			ans = num1+num2;
			printf("%f\n", ans);
			break;
		case '-': 
			ans = num1-num2;
			printf("%f\n", ans);
			break;
		case 'x':
		case '*':
		case 'X': 
			ans = num1*num2;
			printf("%f\n", ans);
			break;
		case '^': 
			ans = pow(num1, num2);
			printf("%f\n", ans);
			break;
		case '/': 
			if (num2 == 0) {
				printf("Error! Division by Zero!\n");
			} else {
				ans = num1 / num2;
				printf("%f\n", ans);
			}
			break;
		default: 
			printf("%c is not a valid operator!\n", operator);
	}
	return 0;
}
/**
*Returns the current time to the user
**/
int getTime(){
	time_t x = time(NULL);
	struct tm tm = *localtime(&x);
	printf("Time Now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	return 0;
}
/**
 * Returns the index if the params contain the term. If the params
 * don't contain the term this returns -1.
 *
 * @param 	params 	char * array
 * @param 	term	char * containing the search term
 * @return 	int containing location of the term
 */
int has_term(char *params[], char *term) {
	int i = 0;
	
	while (params[i]) {
		if (strcmp(params[i++], term) == 0) {
			return i - 1;
		}
	}
	return -1;
}

/**
 * Splits the parameters into left and right at the location of the character '|'
 *
 * @param 	params	the params array
 * @param 	left	the left array
 * @param 	right	the right array
 * @return 	boolean	true/false representing success/fail
 */
int split_params(char *params[], char *left[], char *right[]) {
	int loc = 0;
	if ((loc = has_term(params, "|")) != -1) {
		int i = 0;
		while (params[i] != NULL) {
			if (i < loc) {
				left[i] = params[i];
			} else if (i > loc) {
				right[i-loc-1] = params[i];
			}
		}
		left[loc] = NULL;
		return 1;
	} else {
		return 0;
	}
}

/**
 * Receives an array of commands terminated by a NULL and executes the
 * commands. This section also holds all the extra functionality.
 *
 * @param params is an array of char *
 * @param num_words is the number of words in the command
 */
void execute_command(char *params[], int num_words) {
	pid_t pid[2];
	int pipe_fd[2];
	int has_pipe = 0;
	
	if (has_term(params, "|") != -1) {
		pipe(pipe_fd);
		has_pipe = 1;
	}
	
	if (strcmp("cd", params[0]) == 0) {
		int result = chdir(params[1]);
		
		if (!result) {
			char cwd[1024];
			getcwd(cwd, sizeof(cwd));
			printf("Current working dir:\n%s\n", cwd);
		} else if (strlen(params[1]) == 1) {
			printf("This system does not support \"cd %s\" functionality.\n", params[1]);
		} else {
			printf("Could not locate directory \"%s\".\n", params[1]);
		}
		
		if (result) {
			printf("[gshell: program terminated abnormally][%d]\n", result);
		} else {
			printf("[gshell: program terminated successfully]\n");
		}
	} else if ((pid[0] = Fork()) == 0) { // Child process
		char cmd[LINE_LEN];
		sprintf(cmd, "/bin/%s", params[0]);
		
		if (strcmp("google", params[0]) == 0)  {
			exit(system("firefox http://www.google.com/ &"));
		} else if (strcmp("calc", params[0]) == 0){
			if (num_words == 4) {
				float num1 = atof(params[1]), num2 = atof(params[3]);
				char operator = params[2][0];
				
				exit(calculator(num1, num2, operator));
			} else {
				printf("calc requires the form \"calc [num1] [op] [num2]\"\n");
				exit(-1);
			}
		} else if(strcmp("time", params[0]) == 0){
			exit(getTime());
		} else {
			int loc, fd;
			if ((loc = has_term(params, ">")) != -1) {
				fd = open(params[loc+1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
				params[loc] = NULL;
				
				dup2(fd, 1); //stdout
				dup2(fd, 2); //stderr
				
				close(fd);
			} else if ((loc = has_term(params, "<")) != -1) {
				fd = open(params[loc+1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
				params[loc] = NULL;
				
				dup2(fd, 0); //stdout
				dup2(fd, 2); //stderr
				
				close(fd);
			} else if ((loc = has_term(params, "|")) != -1) {
				if ((pid[1] = Fork()) != 0) { // First Child
					if ((fd = dup2(pipe_fd[1], 0)) == -1) { // stdout
						perror("Child1 - Dup2");
					}
					if (close(pipe_fd[0])) { perror("Pipe Close 0"); }
					if (close(pipe_fd[1])) { perror("Pipe Close 1"); }
					
					params[loc] = NULL;
					exit(execvp(cmd, params));
				} else { // Second Child
					if ((fd = dup2(pipe_fd[0], 1)) == -1) { // stdin
						perror("Child2 - Dup2");
					}
					if (close(pipe_fd[0])) { perror("Pipe Close 0"); }
					if (close(pipe_fd[1])) { perror("Pipe Close 1"); } 
					
					sprintf(cmd, "/bin/%s", params[loc+1]);
					exit(execvp(cmd, &params[loc+1]));
				}
			}
			exit(Execv(cmd, params));	
		}
	} else { // Parent must wait
		int result[2];
		
		if (has_pipe) {
			if (close(pipe_fd[0])) { perror("Pipe Close 0"); }
			if (close(pipe_fd[1])) { perror("Pipe Close 1"); }
		}
		
		waitpid(pid[0], &result[0], 0);
		if (has_pipe) {
			waitpid(pid[1], &result[1], 0);
		}
		
		if (result[0]) {
			printf("[gshell: program terminated abnormally][%d]\n", result[0]);
		} else if (result[1]) {
			printf("[gshell: program terminated abnormally][%d]\n", result[1]);
		} else {
			printf("[gshell: program terminated successfully]\n");
		}
	}
}

/**
 * Receives a string with multiple commands and executes all of them
 * 
 */
void execute_commands(char *string, int *words, int lines) {
	char *tok_string = calloc(LINE_LEN, sizeof(char));
	strcpy(tok_string, string);
	char *word = strtok(tok_string, " ");
	int l;
	for (l = 0; l < lines; l++) {
		char *params[words[l] + 1];
		
		/* ===== Split up words ===== */
		int i = 0;
		while (word != NULL && i < words[l]) {
			if (word[0] != ';') {
				if (word[strlen(word) - 1] == ';') {
					word[strlen(word) - 1] = 0;
				}
				params[i++] = word;
			}
			word = strtok(NULL, " \n");
		}
		
		if (params[i - 1][strlen(params[i-1]) - 1] == '\n') {
			params[i - 1][strlen(params[i-1]) - 1] = 0;
		}
		params[i] = NULL;
		
		/* ===== Execute command ===== */
		execute_command(params, words[l]);
	}	
}

int main(int argc, char *argv[]) {
	int prev_newline = 0;
	int prev_newtab = 0;
	
	struct clist *com_buf = clist_create(LINE_LEN);
	
	while (1) {
		/* ===== Print the prompt string ===== */
		printf("gshell> ");
		
		/* ===== Receive user input ===== */
		char *new_line = get_command(com_buf, &prev_newtab);
		char *tok_string = calloc(LINE_LEN, sizeof(char));
		strcpy(tok_string, new_line);
		
		/* ===== Update Buffer ===== */
		if (clist_num_elems(com_buf) == 0 || strcmp(clist_iter_begin(com_buf), new_line)) {
			clist_add_front(com_buf, new_line);
		}
		
		/* ===== Handle user input ===== */
		int l, lines = 0;
		int *words = get_word_count(new_line, &lines);
		
		if (prev_newtab < 2 && lines > 0) {
			
			/* ===== Execute commands ===== */
			char *word = strtok(tok_string, " ");
			for (l = 0; l < lines; l++) {
				char *params[words[l] + 1];
				
				/* ===== Split up words ===== */
				int i = 0;
				while (word != NULL && i < words[l]) {
					if (word[0] != ';') {
						if (word[strlen(word) - 1] == ';') {
							word[strlen(word) - 1] = 0;
						}
						params[i++] = word;
					}
					word = strtok(NULL, " \n");
				}
				
				if (params[i - 1][strlen(params[i-1]) - 1] == '\n') {
					params[i - 1][strlen(params[i-1]) - 1] = 0;
				}
				params[i] = NULL;
				
				/* ===== Execute command ===== */
				execute_command(params, words[l]);
			}
			
			prev_newline = 0;
		} else if (prev_newline || prev_newtab) { // [Enters][Enter] or [tab][tab]
			prev_newline = 0;
			prev_newtab = 0;
			
			if (Fork() == 0) {
				char *args[] = {"ls", NULL};
				Execv("/bin/ls", args);
			}
			
			int result;
			
			if ((result = Wait(NULL)) == ERROR) {
				printf("[gshell: program terminated abnormally][%d]\n", result);
			} else {
				printf("[gshell: program terminated successfully]\n");
			}
		} else {
			prev_newline = 1;
		}
	}
	
}
