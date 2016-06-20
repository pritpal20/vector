#include <cstdio>
#include <cstring>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MIN_N = 100000;
const int MAX_N = 1000000;
const int M = 65536;
const int Q = 100000;

int main() {
	int i, sz, n, q;
	freopen("input.txt", "w", stdout);
	srand(time(0));
	n = MIN_N + rand() % (MAX_N - MIN_N + 1);
	printf("%d\n", n);
	for (i = 0; i < n; i++) 
		printf("%d ", rand() % M);
	puts("");
	sz = n;
	q = Q;
	printf("%d\n", q);
	while (q--) {
		int sel = rand() % 10;
		if (sel < 5) {
			printf("0 %d %d\n", rand() % M, rand() % M);
			sz += 2;
		} else if (sel < 8) {
			printf("1 2 3\n");
			--sz;
		} else {
			int st = rand() % (sz - 10);
			int ed = st + 1 + rand() % 10;
			printf("2 %d %d\n", st, ed);
			sz -= ed - st;
		}
	}
	return 0;
}
