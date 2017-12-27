#
# Makefile for SunPass Vehicles
# 10/09/15
#

cflags = -I. 
CC     = clang++ -std=c++11

AREA51  = /home/courses/cop3330p/LIB/area51

standard: tester.x 
assess:   testerHybrid.x testerCorrect.x
all:      standard assess

tester.x: tester.o shapes.o vehicles.o
	$(CC) -otester.x tester.o shapes.o vehicles.o

testerHybrid.x: $(AREA51)/tester_i.o shapes.o vehicles.o
	$(CC) -otesterHybrid.x $(AREA51)/tester_i.o  shapes.o vehicles.o

tester.o: shapes.h vehicles.h tester.cpp
	$(CC) $(cflags) -c tester.cpp

shapes.o: shapes.h shapes.cpp
	$(CC) $(cflags) -c shapes.cpp

vehicles.o: shapes.h vehicles.h vehicles.cpp
	$(CC) $(cflags) -c vehicles.cpp

testerCorrect.x: $(AREA51)/tester_i.x
	cp $(AREA51)/tester_i.x testerCorrect.x
	chmod 700 testerCorrect.x

# Note that in the hybrid versions, different header files are used. If the
# student vehicles.h and the "correct" vehicles.h do not have the same footprint
# layout, there can be runtime issues because function addresses are calculated
# using one footprint whereas they may be in a different place in the code due
# to using a different class definition.  Thus the hybrid builds are a good test
# of the API correctness, but they are not so good for runtime testing. In a
# normal team environment, the entire team would use the same set of header
# files.
