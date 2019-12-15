# This is a makefile for the person database system
CC = gcc
CFLAGS = -g -Wall
CCLINK = $(CC)
LIBS = 
OBJS = test1.o dict.o hash.o
RM = rm -f

# Creating the executables
all: test1 

test1: $(OBJS)
	$(CCLINK) -o test1 $(OBJS) $(LIBS)

# Creating object files using default rules
hash.o: hash.c hash.h
dict.o: dict.c dict.h hash.h
test1.o: test1.c hash.h dict.h

# Cleaning old files before new make
clean:
	$(RM) test1 *.o *.bak *~ "#"* core
