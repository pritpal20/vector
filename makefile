.PHONY: clean

all: tester

tester: vector.h vector.cpp tester.cpp
	g++ -std=c++11 tester.cpp -o tester

tester_dbg: vector.h vector.cpp tester.cpp
	g++ -std=c++11 -D DEBUG tester.cpp -o tester_dbg

clean:
	rm tester || true
	rm tester_dbg || true
