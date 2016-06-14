# vector

:purple_heart: A 2.3x faster std::vector proof-of-concept/partial implementation.  
This is meant to show you why you should ditch C++ STLs when performance is critical.

[![Build Status](https://travis-ci.org/lnishan/vector.svg?branch=master)](https://travis-ci.org/lnishan/vector)

It's just a proof-of-concept (for now at least),  
which means it's **NOT** standard-compliant and lacks many, many implementation details.


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
`make && ./tester`

```
lni::vector 0.105s
std::vector 0.242s
```


## License

[![Creative Commons Attribution 4.0 International](https://i.creativecommons.org/l/by/4.0/88x31.png)](http://creativecommons.org/licenses/by/4.0/)

lni::vector by Jasmine "lnishan" Chen is licensed under a [Creative Commons Attribution 4.0 International License](http://creativecommons.org/licenses/by/4.0/).
