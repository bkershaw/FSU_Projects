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

all: fhtbl.x fhtblMM.x fhtblKISS.x fhtblSimple.x rantable.x hashcalc.x

fhtbl.x: fhtbl.o
	$(CC) -ofhtbl.x fhtbl.cpp  

fhtbl.o: fhtbl.cpp $(TCPP)/hashclasses.h $(TCPP)/compare.h hashtbl.h
	$(CC) -c fhtbl.cpp

fhtblMM.x: fhtblMM.o
	$(CC) -ofhtblMM.x fhtblMM.cpp  

fhtblMM.o: fhtblMM.cpp $(TCPP)/hashclasses.h $(TCPP)/compare.h hashtbl.h
	$(CC) -c fhtblMM.cpp

fhtblKISS.x: fhtblKISS.o
	$(CC) -ofhtblKISS.x fhtblKISS.cpp  

fhtblKISS.o: fhtblKISS.cpp $(TCPP)/hashclasses.h $(TCPP)/compare.h hashtbl.h
	$(CC) -c fhtblKISS.cpp

fhtblSimple.x: fhtblSimple.o
	$(CC) -ofhtblSimple.x fhtblSimple.cpp  

fhtblSimple.o: fhtblSimple.cpp $(TCPP)/hashclasses.h $(TCPP)/compare.h hashtbl.h
	$(CC) -c fhtblSimple.cpp

hashcalc.x: xstring.o hashfunctions.o
	$(CC) -ohashcalc.x hashcalc.cpp 

rantable.x: xstring.o xran.o xranxstr.o
	$(CC) -orantable.x rantable.cpp 

hashfunctions.o: $(CPP)/hashfunctions.cpp $(CPP)/hashfunctions.h
	$(CC) -c $(CPP)/hashfunctions.cpp	

xstring.o: $(CPP)/xstring.cpp $(CPP)/xstring.h
	$(CC) -c $(CPP)/xstring.cpp

xran.o: $(CPP)/xran.cpp $(CPP)/xran.h
	$(CC) -c $(CPP)/xran.cpp

xranxstr.o: $(CPP)/xranxstr.cpp $(CPP)/xranxstr.h
	$(CC) -c $(CPP)/xranxstr.cpp

