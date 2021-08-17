CC = g++
CFLAGS =

main.watch: main.cpp *.hpp
	ls main.cpp *.hpp | entr -s "clear && g++ -o main main.cpp $(CFLAGS) && ./main"