# vector

:purple_heart: A 2.3x faster std::vector proof-of-concept/partial implementation.  

[![Build Status](https://travis-ci.org/lnishan/vector.svg?branch=master)](https://travis-ci.org/lnishan/vector)

This is meant to show you why you should ditch C++ STLs when performance is critical.

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

`make && ./tester`

---

> Homebrew-gcc 6.1.1, Mac OSX El Capitan, Macbook Air Early 2014

```
lni::vector 0.105s
std::vector 0.242s
```

➔ **2.305x** faster

---

> gcc 6.1.1, Ubuntu 16.04 LTS, DigitalOcean VPS (2GB RAM, 1 CPU)

```
lni::vector 0.099s
std::vector 0.238s
```

➔ **2.404x** faster

---

> clang 3.8.0, Ubuntu 16.04 LTS, DigitalOcean VPS (2GB RAM, 1 CPU)

```
lni::vector 0.103s
std::vector 0.239s
```

➔ **2.320x** faster


## License

[![Creative Commons Attribution 4.0 International](https://i.creativecommons.org/l/by/4.0/88x31.png)](http://creativecommons.org/licenses/by/4.0/)

lni::vector by Jasmine "lnishan" Chen is licensed under a [Creative Commons Attribution 4.0 International License](http://creativecommons.org/licenses/by/4.0/).
