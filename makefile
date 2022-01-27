CC = gcc
APP = -o cut
SRC = ./src/main.c
PARAMS = 
LIBS = -lpthread


all: $(src)
	 	$(CC) $(APP) $(SRC) $(LIBS)