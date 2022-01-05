all : parser graph.svg

parser : lexer.cpp parser.cpp parser.hpp
	g++ -std=c++11 -o $@ $^

lexer.cpp : lexer.ll parser.cpp
	flex -o $@ $<

parser.cpp : parser.yy
	bison -v -d -g -o parser.cpp parser.yy

graph.svg : parser.gv
	dot -Tsvg $^ -o $@
