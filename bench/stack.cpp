#include <cstdio>
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


const int N = 3e7;

int main() {
	int i, n, cnt;
	time_t st;
	unsigned long long ans = 0;

	// create a seemingly randomized but deterministic input
	vec<int> inp{233, 7, 64, 13, 32, 150, 198, 241, 121, 71};
	inp.resize(N);
	for (i = 10; i < N; ++i)
		inp[i] = (inp[i / 2] * inp[i - 1] * inp[i - 2]) % 255 + 1;

	// start solving
	st = clock();
	vec<int> stk;
	for (auto &ai: inp) {
		if (stk.empty() || stk.back() > ai)
			stk.push_back(ai);
		else {
			cnt = 0;
			while (!stk.empty() && stk.back() <= ai) {
				++cnt;
				stk.pop_back();
			}
			ans += cnt * (cnt - 1) / 2;
		}
	}
	printf("%llu\n", ans);
	printf("%.3fs\n", (double)(clock() - st) / CLOCKS_PER_SEC);

	return 0;
}
