CPPFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3
vector2d: code.o
	g++ -o code code.o
code.o: code.cpp
	g++ $(CPPFLAGS) -c code.cpp
