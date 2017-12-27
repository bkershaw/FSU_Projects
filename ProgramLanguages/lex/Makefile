all: ex1.exe

ex1.exe: lex.yy.c
	gcc -o $@ $< -lfl

lex.yy.c: ex1.l
	flex $<
clean: 
	rm -f lex.*.y ex1.exe *~ lex.yy* 


