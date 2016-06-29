.PHONY: clean

CC = g++


all: \
	std_array_op \
	lni_array_op \
	folly_array_op \
	std_insertion \
	lni_insertion \
	folly_insertion \
	std_back_insertion \
	lni_back_insertion \
	folly_back_insertion \
	std_stack \
	lni_stack \
	folly_stack


std_array_op: array_op.cpp ../vector.hpp
	$(CC) -O2 -std=c++11 array_op.cpp -o std_array_op

lni_array_op: array_op.cpp ../vector.hpp
	$(CC) -O2 -std=c++11 -D USE_LNI_VECTOR array_op.cpp -o lni_array_op

folly_array_op: array_op.cpp ../vector.hpp
	$(CC) -O2 -std=c++11 -lfolly -D USE_FOLLY_VECTOR array_op.cpp -o folly_array_op

std_insertion: insertion.cpp ../vector.hpp
	$(CC) -O2 -std=c++11 insertion.cpp -o std_insertion

lni_insertion: insertion.cpp ../vector.hpp
	$(CC) -O2 -std=c++11 -D USE_LNI_VECTOR insertion.cpp -o lni_insertion

folly_insertion: insertion.cpp ../vector.hpp
	$(CC) -O2 -std=c++11 -lfolly -D USE_FOLLY_VECTOR insertion.cpp -o folly_insertion

std_back_insertion: back_insertion.cpp ../vector.hpp
	$(CC) -O2 -std=c++11 back_insertion.cpp -o std_back_insertion

lni_back_insertion: back_insertion.cpp ../vector.hpp
	$(CC) -O2 -std=c++11 -D USE_LNI_VECTOR back_insertion.cpp -o lni_back_insertion

folly_back_insertion: back_insertion.cpp ../vector.hpp
	$(CC) -O2 -std=c++11 -lfolly -D USE_FOLLY_VECTOR back_insertion.cpp -o folly_back_insertion

std_stack: stack.cpp ../vector.hpp
	$(CC) -O2 -std=c++11 stack.cpp -o std_stack

lni_stack: stack.cpp ../vector.hpp
	$(CC) -O2 -std=c++11 -D USE_LNI_VECTOR stack.cpp -o lni_stack

folly_stack: stack.cpp ../vector.hpp
	$(CC) -O2 -std=c++11 -lfolly -D USE_FOLLY_VECTOR stack.cpp -o folly_stack


clean:
	rm std_array_op || true
	rm lni_array_op || true
	rm folly_array_op || true
	rm std_insertion || true
	rm lni_insertion || true
	rm folly_insertion || true
	rm std_back_insertion || true
	rm lni_back_insertion || true
	rm folly_back_insertion || true
	rm std_stack || true
	rm lni_stack || true
	rm folly_stack || true
