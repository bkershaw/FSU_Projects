#
# makefile for UIntSet project
#

LIB      = /home/courses/cop3330p/LIB/cpp
PROJECT  = .
CC       = clang++ -std=c++11

all:   tests demos

tests: test.x fuintset.x

demos: fbitvect.x

test.x: bitvect.o uintset.o test.o
	$(CC) -o test.x bitvect.o uintset.o test.o

fuintset.x: bitvect.o uintset.o fuintset.o
	$(CC) -o fuintset.x bitvect.o uintset.o fuintset.o

fbitvect.x: bitvect.o fbitvect.o
	$(CC) -o fbitvect.x bitvect.o fbitvect.o

bitvect.o: $(LIB)/bitvect.h $(LIB)/bitvect.cpp
	$(CC) -c -I$(PROJECT) -I$(LIB) $(LIB)/bitvect.cpp

uintset.o: $(LIB)/bitvect.h $(PROJECT)/uintset.h $(PROJECT)/uintset.cpp
	$(CC) -c -I$(PROJECT) -I$(LIB) $(PROJECT)/uintset.cpp

test.o: $(PROJECT)/uintset.h $(PROJECT)/test.cpp
	$(CC) -c -I$(PROJECT) -I$(LIB) $(PROJECT)/test.cpp

fuintset.o: $(PROJECT)/uintset.h $(PROJECT)/fuintset.cpp
	$(CC) -c -I$(PROJECT) -I$(LIB) $(PROJECT)/fuintset.cpp

fbitvect.o: $(LIB)/bitvect.h $(PROJECT)/fbitvect.cpp
	$(CC) -c  -I$(PROJECT) -I$(LIB) $(PROJECT)/fbitvect.cpp
