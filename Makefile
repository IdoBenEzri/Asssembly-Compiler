CXX      := -gcc

project: 
	${CXX} -ansi -pedantic OperatorTable.c MachineCoder.c SymbolTable.c HelpTools.c Assembler.c -o project.exe
