#include <cstdio>
#include <ctime>
#include <vector>
#include "../vector.hpp"

#ifdef USE_LNI_VECTOR
using lni::vector;
#else
using std::vector;
#endif

int main() {
	time_t st;
	int i, n, q;
	int cmd, s, e;
	int add, ai;
	st = clock();
	vector<int> v;
	scanf("%d", &n);
	v.resize(n);
	for (i = 0; i < n; i++)
		scanf("%d", &v[i]);
	scanf("%d", &q);
	while (q--) {
		scanf("%d", &cmd);
		if (cmd == 0) {
			scanf("%d", &add);
			for (i = 0; i < add; ++i) {
				scanf("%d", &ai);
				v.push_back(ai);
			}
		} else if (cmd == 1) {
			v.pop_back();
		} else if (cmd == 2) {
			scanf("%d%d", &s, &e);
			v.erase(v.begin() + s, v.begin() + e);
		}
	}
	long long int sum = 0;
	for (auto &n: v)
		sum += n;
	printf("%lld\n", sum);
	printf("%.3fs\n", (double)(clock() - st) / CLOCKS_PER_SEC);
	return 0;
}
