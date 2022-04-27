compilerFlags = -Wall -std=c++17
linkerFlags = -L/usr/bin/c++ -lncurses -pthread
objs = src/main.o src/ball.o src/paddle.o src/point.o

pong : $(objs)
	g++ -o bin/pong.out $(objs) $(linkerFlags)

ball.o : src/ball.h src/paddle.h src/ball.cpp
	g++ -o src/ball.o -c src/ball.cpp $(compilerFlags)

point.o : src/point.h src/point.cpp
	g++ -o src/point.o -c src/point.cpp $(compilerFlags)

paddle.o : src/paddle.h src/paddle.cpp
	g++ -o src/paddle.o -c src/paddle.cpp $(compilerFlags)

main.o : src/paddle.h src/ball.h src/point.h src/main.cpp
	g++ -o src/main.o -c src/main.cpp $(compilerFlags)

clear :
	rm -f $(objs) bin/*.out -r bin/*.dSYM