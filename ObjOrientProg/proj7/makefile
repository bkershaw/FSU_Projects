# makefile for queue project
# note dependence on provious project

LIB = /home/courses/cop3330p/LIB
PROJ = .

CC = clang++ -std=c++11 -I$(PROJ) -I$(LIB)/cpp

std: fstack.x constTest.x

all: std fstack_char.x fstack_int.x fstack_String.x

fstack.x: fstack.cpp stack.t
	$(CC) -ofstack.x fstack.cpp

constTest.x: constTest.cpp stack.t
	$(CC) -oconstTest.x constTest.cpp

fstack_char.x: fstack_char.cpp stack.t
	$(CC) -ofstack_char.x fstack_char.cpp

fstack_String.x: fstack_String.cpp stack.t
	$(CC) -ofstack_String.x fstack_String.cpp

fstack_int.x: fstack_int.cpp stack.t
	$(CC) -ofstack_int.x fstack_int.cpp

