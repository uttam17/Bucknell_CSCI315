
CC = gcc -I ./include
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG -nostartfiles
 
INC = ./include
SRC = ./src
OBJ = ./obj
DOC = ./doc
BIN = ./bin
 
vpath %.h ./include
vpath %.c ./src
 
EXECS =  memory-test frag-eval get_data
 
all: $(EXECS)
 
doc: doxygen
 
$(OBJ)/dnode.o: dnode.h dnode.c
	$(CC) $(CFLAGS) -c $(SRC)/dnode.c -o $(OBJ)/dnode.o
 
$(OBJ)/dlist.o: dlist.h dlist.c dnode.h
	$(CC) $(CFLAGS) -c $(SRC)/dlist.c -o $(OBJ)/dlist.o
 
$(OBJ)/allocator.o:  $(SRC)/allocator.c dlist.h dnode.h $(OBJ)/dlist.o $(OBJ)/dnode.o allocator.h
	$(CC) $(CFLAGS)  -c  $(SRC)/allocator.c -o $(OBJ)/allocator.o
 
 
frag-eval: $(SRC)/frag-eval.c $(OBJ)/allocator.o $(OBJ)/dnode.o $(OBJ)/dlist.o
	$(CC) $(CFLAGS)  $(OBJ)/dnode.o $(OBJ)/dlist.o $(OBJ)/allocator.o $(SRC)/frag-eval.c -o frag-eval
 
get_data: $(SRC)/get_data.c $(OBJ)/allocator.o $(OBJ)/dnode.o $(OBJ)/dlist.o
	$(CC) $(CFLAGS) $(OBJ)/allocator.o $(OBJ)/dnode.o $(OBJ)/dlist.o $(SRC)/get_data.c -o get_data
.PHONY: clean
clean:
	/bin/rm -rf $(BIN)/* $(OBJ)/* core* *~

