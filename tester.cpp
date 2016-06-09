#include "vector.h"
#include <cstdio>
#include <vector>
#include <ctime>

int main() {
	int i;
	time_t st;

	st = clock();
	lni::vector<int> v1;
	for (i = 0; i < 10000000; ++i)
		v1.push_back(i);
	printf("lni::vector %.3fs\n", (double)(clock() - st) / CLOCKS_PER_SEC);
	
#ifdef DEBUG
	puts("Testing resize ...");
	v1.resize(5);
	for (auto &n: v1)
	 	printf("%d ", n);
	puts("");

	puts("Testing initializer list ...");
	lni::vector<int> v2 = {10, 11, 12, 13, 14};
	for (auto &n: v2)
		printf("%d ", n);
	puts("");

	puts("Testing swap ...");
	v1.swap(v2);
	for (auto &n: v1)
		printf("%d ", n);
	puts("");
	for (auto &n: v2)
		printf("%d ", n);
	puts("");
#endif

	v1.clear();
	for (auto &n: v1)
		printf("%d ", n);
	puts("");
	
	st = clock();
	std::vector<int> std_v1;
	for (i = 0; i < 10000000; ++i)
		std_v1.push_back(i);
	printf("std::vector %.3fs\n", (double)(clock() - st) / CLOCKS_PER_SEC);

	return 0;
}
