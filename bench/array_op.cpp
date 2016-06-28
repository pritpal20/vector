#include <cstdio>
#include <ctime>
#include <vector>
#include "../vector.hpp"


#if defined(USE_LNI_VECTOR)

template <typename T>
using vec = lni::vector<T>;

#else

template <typename T>
using vec = std::vector<T>;

#endif


const int N = 1e6;
const int Q = 1e5;

int main() {
	int i, k;
	time_t st;
	int cmd, s, e;
	int add, ai;
	st = clock();
	vec<int> v;
	v.resize(N);
	for (i = 0; i < N; i++)
		v[i] = i;
	for (k = 0; k < Q; k++) {
		cmd = k % 10;
		if (cmd < 5) {
			add = 7;
			for (i = 0; i < add; ++i) {
				v.push_back(k);
			}
		} else if (cmd < 8) {
			v.pop_back();
		} else {
			v.erase(v.begin() + v.size() / 2, v.begin() + v.size() / 2 + 7);
		}
	}
	long long int sum = 0;
	for (auto &n: v)
		sum += n;
	printf("%lld\n", sum);
	printf("%.3fs\n", (double)(clock() - st) / CLOCKS_PER_SEC);
	return 0;
}
