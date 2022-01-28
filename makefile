CC = gcc
APP = -o cut

EVENT = ./src/events/event.c ./src/events/eventsmanager.c
EVENT_TEST = ./tests/eventsTests.c
EVENT_MANAGER = ./tests/eventsManagerTests.c
EVENT_PARAMS = -o ./tests/eventsTests

SRC = ./src/main.c 
PARAMS = 
LIBS = -lpthread


all: $(EVENT) $(SRC)
	 	$(CC) $(APP) $(EVENT) $(SRC) $(LIBS)

eventTest: $(EVENT) $(EVENT_TEST) 
				$(CC) $(EVENT_PARAMS) $(EVENT) $(EVENT_TEST) $(LIBS)

eventsManagerTests: $(EVENT) $(EVENT_MANAGER) 
						$(CC) $(EVENT_PARAMS) $(EVENT) $(EVENT_MANAGER) $(LIBS)