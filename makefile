.PHONY: clean

CC = g++


all: tester dbg

tester: vector.hpp tester.cpp
	$(CC) -O2 -std=c++11 -Wall tester.cpp -o tester

dbg: vector.hpp tester.cpp
	$(CC) -O2 -std=c++11 -Wall -D DEBUG tester.cpp -o dbg

clean:
	rm tester || true
	rm dbg || true
