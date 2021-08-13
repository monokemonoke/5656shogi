CC = g++
CFLAGS = -std=c++11
TARGET = 5656shogi
OBJS = board.o test.o game.o log.o test_log.o koma.o
5656shogi:  board.o test.o game.o koma.o log.o
	$(CC) $(CFLAGS) game.o board.o test.o log.o koma.o -o 5656shogi && make removeObj
board.o: board.cpp board.hpp
	$(CC) $(CFLAGS) -o board.o -c board.cpp
koma.o: koma.cpp koma.hpp
	$(CC) $(CFLAGS) -o koma.o -c koma.cpp
test.o: test.cpp
	$(CC) $(CFLAGS) -o test.o -c test.cpp
game.o: game.cpp game.hpp
	$(CC) $(CFLAGS) -o game.o -c game.cpp

log: log.o test_log.o
	$(CC) $(CFLAGS) log.o test_log.o -o log 
log.o: log.cpp log.hpp
	$(CC) $(CFLAGS) -o log.o -c log.cpp
test_log.o: test_log.cpp
	$(CC) $(CFLAGS) -o test_log.o -c test_log.cpp

clear:
	rm -rf $(OBJS) $(TARGET) $(DOCS) 
removeObj:
	rm -rf $(OBJS)