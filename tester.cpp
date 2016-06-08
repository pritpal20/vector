#include "vector.h"

using lni::vector;

int main() {
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.emplace_back(4);
	v.emplace_back(5);
	v.emplace_back(6);
	for (auto &n: v)
		printf("%d\n", n);
	return 0;
}
