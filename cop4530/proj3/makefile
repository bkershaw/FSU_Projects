# makefile for WordSmith project
# Blake Kershaw
# COP4530
# February 11th, 2017

HOME   = /home/courses/cop4530p/LIB
CPP    = $(HOME)/cpp
TCPP   = $(HOME)/tcpp
AREA51 = $(HOME)/area51
TESTS  = $(HOME)/tests

#CC     = g++ -std=c++11 -Wall -Wextra -I. -I$(CPP) -I$(TCPP)
CC     = clang++ -std=c++11 -I. -I$(CPP) -I$(TCPP)

# -Weverything -Wno-old-style-cast

all: ws.x

ws.x: main_ws.o wordsmith.o xstring.o
	$(CC) -ows.x xstring.o wordsmith.o main_ws.o

main_ws.o: wordsmith.h  main_ws.cpp
	$(CC) -c main_ws.cpp
	   	   
wordsmith.o: wordsmith.h wordsmith.cpp cleanup.cpp
	$(CC) -c wordsmith.cpp

xstring.o: $(CPP)/xstring.cpp $(CPP)/xstring.h
	$(CC) -c $(CPP)/xstring.cpp

