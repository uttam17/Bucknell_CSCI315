CC = gcc -I ./include
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

INC = ./include
SRC = ./src
OBJ = ./obj
DOC = ./doc
BIN = ./bin

vpath %.h ./include
vpath %.c ./src

EXECS = gshell buffer_test

all: $(EXECS)

$(OBJ)/buffer.o: $(INC)/buffer.h $(SRC)/buffer.c
	$(CC) $(CFLAGS) -c $(SRC)/buffer.c -o $(OBJ)/buffer.o
	
$(OBJ)/cnode.o: $(INC)/cnode.h $(SRC)/cnode.c
	$(CC) $(CFLAGS) -c $(SRC)/cnode.c -o $(OBJ)/cnode.o
	
$(OBJ)/clist.o: $(INC)/cnode.h $(INC)/clist.h $(SRC)/clist.c
	$(CC) $(CFLAGS) -c $(SRC)/clist.c -o $(OBJ)/clist.o

$(OBJ)/wrappers.o: $(INC)/wrappers.h $(SRC)/wrappers.c
	$(CC) $(CFLAGS) -c $(SRC)/wrappers.c -o $(OBJ)/wrappers.o
	
buffer_test: $(SRC)/buffer_test.c $(OBJ)/buffer.o
	$(CC) $(CFLAGS) $(OBJ)/buffer.o $(SRC)/buffer_test.c -o $(BIN)/buffer_test

gshell: $(SRC)/gshell.c $(OBJ)/wrappers.o $(OBJ)/buffer.o $(OBJ)/clist.o $(OBJ)/cnode.o
	$(CC) $(CFLAGS) $(OBJ)/wrappers.o $(OBJ)/buffer.o $(OBJ)/clist.o $(OBJ)/cnode.o $(SRC)/gshell.c -o $(BIN)/gshell -lm
	
.PHONY: clean
clean:
	/bin/rm -rf $(EXECS)