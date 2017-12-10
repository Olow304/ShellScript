# Makefile
# Vedant Chaudhari, Saleban Olow
# Champlain College
# CSI-230-02 -- Fall 2017 -- Linux / Unix Programming

# Compiler
CC=g++

# Flags
CFLAGS=-Wall -c

# Source files
SOURCES=main.cpp init.cpp help.cpp exit.cpp cd.cpp

# Objects: takes each source and substitutes .o for .cpp
OBJECTS=$(SOURCES:.cpp=.o)

# Define program name
EXECUTABLE=classicshell

# First/default target, called all by convention
all: $(EXECUTABLE)

# target builds the file, depends on all .o files
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o classicshell

# This is a suffix rule
# $< is the name of the first dependency, $@ is the target
# This compiles each .cpp file to a .o file
.cpp.o: $(SOURCES)
	$(CC) $(FLAGS) $< -o $@

# Clean target, delete all generate files
clean:
	rm *.o classicshell
