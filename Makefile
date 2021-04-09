compile_script:
	- bison -dv trabalho.y
	- flex trabalho.lex
	- gcc entr.c lex.yy.c bytecode.c lexico.c lista.c sintatico.c tabsimb.c tipo.c trabalho.tab.c -lm -g

bytecode_to_jasmin_and_execute:
	- java -jar jasmin-2.4/jasmin.jar java_bytecode.j
	- java java_class

full_test:
	- bison -dv trabalho.y
	- flex trabalho.lex
	- gcc entr.c lex.yy.c bytecode.c lexico.c lista.c sintatico.c tabsimb.c tipo.c trabalho.tab.c -lm -g
	- ./a.out test.txt
	- java -jar jasmin-2.4/jasmin.jar java_bytecode.j
	- java java_class

.PHONY: clean

clean:
	-rm *.out
	-rm *.class
	-rm *.j
	-rm trabalho.output
	-rm trabalho.tab.c
	-rm trabalho.tab.h
