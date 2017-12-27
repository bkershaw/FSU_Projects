# makefile for WordSmith project
# Blake Kershaw
# COP4530
# March 1st, 2017

HOME   = /home/courses/cop4530p/LIB
CPP    = $(HOME)/cpp
TCPP   = $(HOME)/tcpp
AREA51 = $(HOME)/area51
TESTS  = $(HOME)/tests

#CC     = g++ -std=c++11 -Wall -Wextra -I. -I$(CPP) -I$(TCPP)
CC     = clang++ -std=c++11 -I. -I$(CPP) -I$(TCPP)

# -Weverything -Wno-old-style-cast

all: fmap.x mmap.x ws3.x

fmap.x: fmap.o 
	$(CC) -ofmap.x fmap.o  

fmap.o: fmap.cpp map_adt.h mapiter_adt.h
	$(CC) -c fmap.cpp

mmap.x: mmap.o
	$(CC) -ommap.x mmap.o

mmap.o: map_adt.h mmap.cpp
	$(CC) -c mmap.cpp

ws3.x: main_ws3.o wordsmith3.o xstring.o
	$(CC) -ows3.x xstring.o wordsmith3.o main_ws3.o

main_ws3.o: wordsmith3.h  main_ws3.cpp
	$(CC) -c main_ws3.cpp
	   	   
wordsmith3.o: wordsmith3.h wordsmith3.cpp cleanup.cpp
	$(CC) -c wordsmith3.cpp

xstring.o: $(CPP)/xstring.cpp $(CPP)/xstring.h
	$(CC) -c $(CPP)/xstring.cpp

