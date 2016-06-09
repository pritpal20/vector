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
	
	puts("\n=== Debugging Messages ===\n");
	puts("Testing resize ...");
	v1.resize(5);
	for (auto &n: v1)
	 	printf("%d ", n);
	puts("\n");

	puts("Testing front and back");
	printf("%d %d", v1.front(), v1.back());
	puts("\n");

	puts("Testing [] operator overloading ... ");
	v1[0] = 1;
	int sz = v1.size();
	for (i = 0; i < sz; i++)
		printf("%d ", v1[i]);
	puts("\n");

	puts("Testing initializer list ...");
	lni::vector<int> v2 = {10, 11, 12, 13, 14};
	for (auto &n: v2)
		printf("%d ", n);
	puts("\n");

	puts("Testing swap ...");
	v1.swap(v2);
	for (auto &n: v1)
		printf("%d ", n);
	puts("");
	for (auto &n: v2)
		printf("%d ", n);
	puts("\n");

	puts("Testing clear ...");
	v1.clear();
	for (auto &n: v1)
		printf("%d ", n);
	puts("\n");

#endif
	
	st = clock();
	std::vector<int> std_v1;
	for (i = 0; i < 10000000; ++i)
		std_v1.push_back(i);
	printf("std::vector %.3fs\n", (double)(clock() - st) / CLOCKS_PER_SEC);

	return 0;
}
