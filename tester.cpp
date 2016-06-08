#include "vector.h"
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
//	for (auto &n: v1)
//	 	printf("%d ", n);
	
	st = clock();
	std::vector<int> v2;
	for (i = 0; i < 10000000; ++i)
		v2.push_back(i);
	printf("std::vector %.3fs\n", (double)(clock() - st) / CLOCKS_PER_SEC);

	return 0;
}
