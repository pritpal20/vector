.PHONY: clean

CC = g++


all: tester dbg mytester

tester: vector.hpp tester.cpp
	$(CC) -O2 -std=c++11 -Wall tester.cpp -o tester

mytester: vector.hpp mytester.cpp
	$(CC) -O2 -std=c++11 -Wall mytester.cpp -o mytester

dbg: vector.hpp tester.cpp
	$(CC) -O2 -std=c++11 -Wall -D DEBUG tester.cpp -o dbg

clean:
	rm tester || true
	rm mytester || true
	rm dbg || true
