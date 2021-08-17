CC = g++
CFLAGS =
DEPS = matrix.hpp test.hpp

main.build: main.cpp matrix.hpp test.hpp
	$(CC) -o main main.cpp $(CFLAGS)

main.run: main.cpp matrix.hpp test.hpp
	$(CC) -o main main.cpp $(CFLAGS) && ./main

main.watch: main.cpp matrix.hpp test.hpp
	ls main.cpp matrix.hpp test.hpp | entr -s "clear && g++ -o main main.cpp $(CFLAGS) && ./main"