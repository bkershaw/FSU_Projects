all: cxref.exe

cxref.exe: lex.yy.cc
	g++ -o $@ $< -lfl

lex.yy.cc: cxref.l
	flex -o $@ $<
clean:
	rm -f lex.yy.* *.exe *~


