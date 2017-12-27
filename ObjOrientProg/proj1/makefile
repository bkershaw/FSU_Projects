# makefile for stats project

HOME   = /home/courses/cop3330p/LIB
CPP    = $(HOME)/cpp
AREA51 = $(HOME)/area51

#CC     = g++ -std=c++11 -Wall -Wextra -I. -I$(CPP)
CC     = clang++ -std=c++11 -I. -I$(CPP)

# -Weverything -Wno-old-style-cast

all:    stats.x ranint.x test.x

test.x: $(AREA51)/stats_client_i.o stats.o
	$(CC) -otest.x $(AREA51)/stats_client_i.o  stats.o

stats.x: main.o stats.o
	$(CC) -ostats.x stats.o main.o

stats.o: stats.h stats.cpp
	$(CC) -c stats.cpp

main.o: stats.h main.cpp
	$(CC) -c main.cpp

ranint.x: ranint.o xran.o
	$(CC) -oranint.x ranint.o xran.o

ranint.o: $(CPP)/xran.h ranint.cpp
	$(CC) -c ranint.cpp

ranuint.x: ranuint.o xran.o
	$(CC) -oranuint.x ranuint.o xran.o

ranuint.o: $(CPP)/xran.h ranuint.cpp
	$(CC) -c ranuint.cpp

xran.o: $(CPP)/xran.h $(CPP)/xran.cpp
	$(CC) -c $(CPP)/xran.cpp

