SOURCES=  bool.y  scan.l 
objects = bool.o scan.o

BISON=bison
FLEX=flex
CC=gcc
CFLAGS = -O0 -g -c

TARGET = bool.exe
all: $(TARGET)

bool.exe: ${objects}
	${CC} -o $@ ${objects} -lfl 

.SUFFIXES: .c .y .l .o .e

.y.c:
	${BISON} -d -o `basename $< .y`.c  $<
.l.c:   
	${FLEX} -o `basename $< .l`.c  $<
.c.o:
	${CC} ${CFLAGS} $<


clean:
	rm -rf bool.exe *.o *~ scan.c bool.c bool.h y.tab.c y.tab.h

