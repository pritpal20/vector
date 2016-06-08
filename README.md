# vector

A proof-of-concept/partial implementation to demonstrate how fast std::vector could have been

*This is currently a side project and may not be actively updated.*  
*It's also* **NOT** *standard-compliant at this moment*


## Usage

```cpp
#include "vector.h"

int main() {
	int i;
	lni::vector<int> v1;
	for (i = 0; i < 10000000; ++i)
		v1.push_back(i);
	for (auto &n: v1)
	 	printf("%d ", n);

	return 0;
}
```


## Test Results

Homebrew-gcc 6.1.0  
`g++ tester.cpp && ./a.out`

```
lni::vector 0.105s
std::vector 0.242s
```


## License

[![Creative Commons Attribution 4.0 International](https://i.creativecommons.org/l/by/4.0/88x31.png)](http://creativecommons.org/licenses/by/4.0/)

lni::vector by Jasmine "lnishan" Chen is licensed under a [Creative Commons Attribution 4.0 International License](http://creativecommons.org/licenses/by/4.0/).