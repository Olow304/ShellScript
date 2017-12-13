
CC=g++

CFLAGS=-Wall -c

SOURCES=Simple.cpp cd.cpp command_handler.cpp initShell.cpp exit.cpp help.cpp

OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=classicShell

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o classicShell
	
.cpp.o: $(SOURCES)
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm *.o classicShell

