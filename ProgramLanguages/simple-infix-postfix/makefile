CC= gcc
CXX= g++
CFLAGS = -g -O0
all: clean inf2pos.exe

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<
.cpp.o:
	$(CXX) $(CFLAGS) -c -o $@ $<

inf2pos.exe: inf2pos.o
	gcc -o $@ $<

clean:
	rm -f *.o *~ \#*\# inf2pos.exe
