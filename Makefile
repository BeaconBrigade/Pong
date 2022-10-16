all: build/main

SRC=src/*.cpp

build/main: $(SRC)
	clang++ -std=c++17 -pthread -lncurses -o build/main $(SRC)

.PHONY: clean
clean:
	rm -rf build/*
