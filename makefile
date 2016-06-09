.PHONY: clean

all: tester

tester: vector.h vector.cpp tester.cpp
	g++ -std=c++11 tester.cpp -o tester

dbg: vector.h vector.cpp tester.cpp
	g++ -std=c++11 -D DEBUG tester.cpp -o dbg

clean:
	rm tester || true
	rm dbg || true
