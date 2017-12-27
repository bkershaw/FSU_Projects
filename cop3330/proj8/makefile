# makefile for queue project
# note dependence on provious project

LIB = /home/courses/cop3330p/LIB
PROJ = .
PREV = ../proj7

CC = clang++ -std=c++11 -I$(PROJ) -I$(PREV) -I$(LIB)/cpp

std: fstack.x fqueue.x in2post.x constTest.x

all: std fstack_char.x fqueue_char.x fstack_int.x fqueue_int.x fstack_String.x fqueue_String.x

fstack.x: $(PREV)/fstack.cpp $(PREV)/stack.t
	$(CC) -ofstack.x $(PREV)/fstack.cpp

fqueue.x: fqueue.cpp queue.t
	$(CC) -ofqueue.x fqueue.cpp

constTest.x: constTest.cpp $(PREV)/stack.t queue.t
	$(CC) -oconstTest.x constTest.cpp

in2post.x: in2post.cpp $(PREV)/stack.t queue.t
	$(CC) -oin2post.x in2post.cpp

fstack_char.x: $(PREV)/fstack_char.cpp $(PREV)/stack.t
	$(CC) -ofstack_char.x $(PREV)/fstack_char.cpp

fstack_String.x: $(PREV)/fstack_String.cpp $(PREV)/stack.t
	$(CC) -ofstack_String.x $(PREV)/fstack_String.cpp

fstack_int.x: $(PREV)/fstack_int.cpp $(PREV)/stack.t
	$(CC) -ofstack_int.x $(PREV)/fstack_int.cpp

fqueue_char.x: fqueue_char.cpp queue.t
	$(CC) -ofqueue_char.x fqueue_char.cpp

fqueue_String.x: fqueue_String.cpp queue.t
	$(CC) -ofqueue_String.x fqueue_String.cpp

fqueue_int.x: fqueue_int.cpp queue.t
	$(CC) -ofqueue_int.x fqueue_int.cpp
