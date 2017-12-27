all: cxref.exe

cxref.exe: lex.yy.c
	gcc -o $@ $< -lfl

lex.yy.c: cxref.l
	flex $<
clean:
	rm -f lex.yy.* *.exe *~


