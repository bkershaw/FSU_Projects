CC= gcc
CXX= g++

all: clean asm.exe


.c.o:
	$(CC) -c -o $@ $<
.cpp.o:
	$(CXX) -c -o $@ $<  -std=c++11

asm.exe: assem.o
	$(CXX) -o assem.o -std=c++11

test: asm.exe
	./asm.exe < sum.asm > my.obj
	diff my.obj sum.obj 
clean:
	rm -f my.obj asm.exe *.o *~ \#*\#


