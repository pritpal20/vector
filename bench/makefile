.PHONY: clean

all: std_array_op lni_array_op

std_array_op: array_op.cpp ../vector.hpp
	g++ -O2 -std=c++11 array_op.cpp -o std_array_op

lni_array_op: array_op.cpp ../vector.hpp
	g++ -O2 -std=c++11 -D USE_LNI_VECTOR array_op.cpp -o lni_array_op

clean:
	rm std_array_op || true
	rm lni_array_op || true
