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

	puts("Testing pop_back");
	v1.pop_back();
	for (auto &n: v1)
		printf("%d ", n);
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


	puts("Testing constructors ... ");
	lni::vector<double> v3(5, 2.0);
	v3[0] = 1.0; v3[4] = 3.0;
	for (auto &f: v3)
		printf("%.3f ", f);
	puts("");
	lni::vector<double> v4(v3);
	for (auto &f: v4)
		printf("%.3f ", f);
	puts("\n");
#endif
	
	st = clock();
	std::vector<int> std_v1;
	for (i = 0; i < 10000000; ++i)
		std_v1.push_back(i);
	printf("std::vector %.3fs\n", (double)(clock() - st) / CLOCKS_PER_SEC);

	return 0;
}
