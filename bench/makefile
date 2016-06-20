.PHONY: clean

all: std lni

std: array_op.cpp ../vector.hpp
	g++ -std=c++11 array_op.cpp -o std

lni: array_op.cpp ../vector.hpp
	g++ -std=c++11 -D USE_LNI_VECTOR array_op.cpp -o lni

clean:
	rm std || true
	rm lni || true
