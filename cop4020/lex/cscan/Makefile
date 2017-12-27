all: cscan.exe

cscan.exe: lex.yy.c
	gcc -o $@ $< -lfl

lex.yy.c: cscan.l
	flex $<
clean:
	rm -f lex.yy.* cscan.exe *~


