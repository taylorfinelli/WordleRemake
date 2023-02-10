# Make file for Wordle Remake

OBJS	= wordle.o 
CC		= g++
CCFLAGS	= -Wall -Wextra -pedantic -std=c++11 -g

all: wordle

wordle: $(OBJS)
	$(CC) $(CCFLAGS) -o wordle $(OBJS)

wordle.o:	wordle.cpp 
	$(CC) $(CCFLAGS) -c wordle.cpp

# clean by removing object files.

clean:
	rm $(OBJS)wordle
