CC = g++
CC_FLAGS = -Wall -pedantic -std=c++11 -O3

EXEC = Rshell
SOURCEDIR = src
BUILDDIR = bin

SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

all: $(OBJECTS)
			mkdir -p $(BUILDDIR)
			$(CC) $(OBJECTS) -o $(BUILDDIR)/$(EXEC)

Rshell: $(OBJECTS)
			mkdir -p $(BUILDDIR)
			$(CC) $(OBJECTS) -o $(BUILDDIR)/$(EXEC)

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

clean:
	rm -f $(EXEC) $(OBJECTS)
	rm -rf $(BUILDDIR)
