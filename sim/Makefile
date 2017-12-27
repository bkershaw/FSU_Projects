CC= gcc
CXX= g++
DEBUG=-O0 -g -c

all: clean asm-template.exe union-sample.exe

.c.o:
	$(CC) -std=c99 $(DEBUG) -c -o $@ $<
.cpp.o:
	$(CXX) $(DEBUG) -c -o $@ $<  -std=c++11

asm-template.exe: assem-template.o
	$(CXX) -o $@ $< 

union-sample.exe: union-sample.o
	$(CXX) -o $@ $< -std=c++11

clean:
	rm -f *.o *~ \#*\#
