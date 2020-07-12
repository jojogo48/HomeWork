CC:=g++
EXE:=Compiler
OBJ:=lex.yy.o y.tab.o

all:$(EXE)
$(EXE):$(OBJ)
	$(CC) $(OBJ) -fpermissive `llvm-config --ldflags --libs` -lpthread -ltinfo -o $(EXE)

$(OBJ):y.tab.cpp lex.yy.cpp
	$(CC) -ggdb -g -O3 -c y.tab.cpp lex.yy.cpp `llvm-config --cxxflags`

y.tab.cpp:clang.y
	bison -d $^ -o $@

lex.yy.cpp:clang.l
	lex -o $@  $^
.PHONY: clean
clean:
	rm -rf $(EXE)
	rm -rf $(OBJ)
	rm -rf *.cpp
	rm -rf *.ll
	rm -rf *.o
	rm -rf *s


