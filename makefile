CC = gcc
APP = -o cut

EVENT = ./src/events/event.c ./src/events/eventsmanager.c
EVENT_TEST = ./tests/eventsTests.c
EVENT_MANAGER = ./tests/eventsManagerTests.c
EVENT_PARAMS = -o ./tests/eventsTests

READER = ./src/reader/reader.c
READER_TEST = ./tests/readerTests.c
READER_PARAMS = -o ./tests/readerTests

ANALYZER = ./src/analyzer/cpu.c ./src/analyzer/analyzer.c
ANALYZER_TEST = ./tests/analyzerTests.c
ANALYZER_PARAMS = -o ./tests/analyzerTests

PRINTER = ./src/printer/printer.c

LOGGER = ./src/logger/logger.c

THREAD = ./src/threads/threads.c

WATCHDOG = ./src/watchdog/watchdog.c

SRC = ./src/main.c 
PARAMS = 
LIBS = -lpthread


all: $(EVENT) $(READER) $(ANALYZER) $(PRINTER) $(WATCHDOG) $(THREAD) $(SRC)
	 	$(CC) $(APP) $(EVENT) $(READER) $(ANALYZER) $(PRINTER) $(THREAD) $(WATCHDOG) $(SRC) $(LIBS)

eventTest: $(EVENT) $(EVENT_TEST) 
				$(CC) $(EVENT_PARAMS) $(EVENT) $(EVENT_TEST) $(LIBS)

eventsManagerTests: $(EVENT) $(EVENT_MANAGER) 
						$(CC) $(EVENT_PARAMS) $(EVENT) $(EVENT_MANAGER) $(LIBS)

readerTests:  $(READER) $(READER_TEST)
				$(CC) $(READER_PARAMS) $(EVENT) $(READER) $(READER_TEST) $(LIBS)						

analyzerTests: $(ANALYZER) $(ANALYZER_TEST)
					$(CC) $(ANALYZER_PARAMS) $(EVENT) $(READER) $(ANALYZER) $(ANALYZER_TEST) $(LIBS)