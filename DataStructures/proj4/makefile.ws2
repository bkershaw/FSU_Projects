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

all: foaa.x foaa+.x ws2.x moaa.x 

moaa.x: moaa.o
	$(CC) -omoaa.x moaa.o

moaa.o: oaa.h moaa.cpp
	$(CC) -c moaa.cpp

foaa+.x: foaa+.o
	$(CC) -ofoaa+.x foaa+.o 

foaa+.o: oaa.h foaa+.cpp
	$(CC) -c foaa+.cpp

foaa.x: foaa.o
	$(CC) -ofoaa.x foaa.o 

foaa.o: oaa.h foaa.cpp
	$(CC) -c foaa.cpp

ws2.x: main_ws2.o wordsmith2.o xstring.o
	$(CC) -ows2.x xstring.o wordsmith2.o main_ws2.o

main_ws2.o: wordsmith2.h  main_ws2.cpp
	$(CC) -c main_ws2.cpp
	   	   
wordsmith2.o: wordsmith2.h wordsmith2.cpp cleanup.cpp
	$(CC) -c wordsmith2.cpp

xstring.o: $(CPP)/xstring.cpp $(CPP)/xstring.h
	$(CC) -c $(CPP)/xstring.cpp

