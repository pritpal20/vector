#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "../vector.hpp"
#include <folly/FBVector.h>


#if defined(USE_LNI_VECTOR)

template <typename T>
using vec = lni::vector<T>;

#elif defined(USE_FOLLY_VECTOR)

template <typename T>
using vec = folly::fbvector<T>;

#else

template <typename T>
using vec = std::vector<T>;

#endif


const int N = 1e5;

int main() {
	int i;
	time_t st;
	
	st = clock();

	vec<int> v;
	for (i = 0; i < N; ++i)
		v.push_back(i);
	for (i = 0; i < N; ++i)
		v.insert(v.begin() + (i >> 1), i);

	printf("%.3fs\n", (double)(clock() - st) / CLOCKS_PER_SEC);
	
	return 0;
}
