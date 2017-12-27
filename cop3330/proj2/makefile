# makefile for product project

HOME   = /home/courses/cop3330p/LIB
CPP    = $(HOME)/cpp
AREA51 = $(HOME)/area51

#CC    = g++ -std=c++11 -Wall -Westra -I. -I$(CPP)
CC     = clang++ -std=c++11 -I. -I$(CPP)

# -Weverything -Wno-old-style-cast

all:	test1.x test2.x Producttest2.x Producttest1.x

Producttest2.x: /home/courses/cop3330p/LIB/area51/Producttest2.x
	cp /home/courses/cop3330p/LIB/area51/Producttest2.x .
	chmod 500 Producttest2.x

Producttest1.x: /home/courses/cop3330p/LIB/area51/Producttest1.x
	cp /home/courses/cop3330p/LIB/area51/Producttest1.x .
	chmod 500 Producttest1.x

test2.x: test2.o product.o
	$(CC) -otest2.x product.o test2.o

test1.x: test1.o product.o
	$(CC) -otest1.x product.o test1.o

product.o: product.h product.cpp
	$(CC) -c product.cpp

test1.o: product.h test1.cpp
	$(CC) -c test1.cpp

test2.o: product.h test2.cpp
	$(CC) -c test2.cpp

