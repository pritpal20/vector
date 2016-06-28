# vector

:purple_heart: A supercharged `std::vector` implementation (minus Allocator).

[![Build Status](https://travis-ci.org/lnishan/vector.svg?branch=master)](https://travis-ci.org/lnishan/vector)

☘ This is meant to show you why you should ditch C++ STLs when performance is critical.  
`lni::vector` should always be faster or just as fast as other implementations. 

☘ Since the implementation is compliant with the current [C++17 Working Draft](http://open-std.org/JTC1/SC22/WG21/docs/papers/2016/n4594.pdf) (minus Allocator),  
`lni::vector` should be a drop-in replacement for `std:vector` in most cases.  

☘ Just note that `lni::vector` can generate redundancies up to 3x the data size (4x total).  
(Consider using `shrink_to_fit()` to remove redundancies, but beware that a memory reallocation would take place.)


## Usage

A very simple sample is provided below.  

For details, refer to [tester.cpp](tester.cpp) or an [online reference](http://en.cppreference.com/w/cpp/container/vector). 

```cpp
#include "vector.hpp"

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

`lni::vector` is tested with all major compilers (gcc 6, clang 3.8 and VS14).  
I've also included some sample test benches and a simple test script.

### Current Benches

* back_insertion
* insertion
* array_op

### Bench Usage

```bash
cd bench
./test.sh {Bench Name}
```

### Bench Results

#### back_insertion

---

> **Hardware:** 50GB Vmware Disk, 4GB RAM, 1 vCore (Guest VM, Host: 1TB SSHD, 16GB RAM, i7-3770)  
> **Environment:** gcc 6.1.1, Kubuntu 16.04 LTS

```
* std::vector
0.364s

* lni::vector
0.189s

* folly::fbvector
0.379s
```

➔ **92 - 100%** faster

---

> **Hardware:** 120GB SSD, 16GB RAM, i7-3770 (Desktop)  
> **Environment:** Visual Studio 2015, Windows 10 Enterprise 64-bit

```
* std::vector
0.651s

* lni::vector
0.261s
```

➔ **149%** faster

---

> **Hardware:** 16GB Persistent Disk, 3.75GB RAM, 1 HyperThread on 2.5GHz Xeon E5 v2 (Google Compute Engine n1-standard-1)  
> **Environment:** gcc 6.1.1, Ubuntu 16.04 LTS

```
* std::vector
0.599s

* lni::vector
0.281s
```

➔ **113%** faster

---

> **Hardware:** 16GB Persistent Disk, 3.75GB RAM, 1 HyperThread on 2.5GHz Xeon E5 v2 (Google Compute Engine n1-standard-1)  
> **Environment:** clang 3.8.0, Ubuntu 16.04 LTS

```
* std::vector
0.443s

* lni::vector
0.253s
```

➔ **75%** faster

---

> **Hardware:** 256GB SSD, 16GB RAM, i5-4260U (MacBook Air Early 2014)  
> **Environment:** gcc 6.1.0, OS X El Capitan

```
* std::vector
0.832s

* lni::vector
0.457s
```

➔ **82%** faster

---

> **Hardware:** 256GB SSD, 16GB RAM, i5-4260U (MacBook Air Early 2014)  
> **Environment:** clang-703.0.31, OS X El Capitan

```
* std::vector
0.789s

* lni::vector
0.487s
```

➔ **62%** faster


## Discussion

### Why is `lni::vector` faster?

*Fact 1.* A **LOT** of people misuse `std::vector`.

*Fact 2.* Memory copying is expensive.

Most `std::vector` implementations are written as [Dynamic Table](https://en.wikipedia.org/wiki/Dynamic_array).  
The *growth factors* for these implementations are usually no greater than 2.  
Also, the initial reserved sizes are usually assigned only 1.

This means:

☘ Memory reallocations are very likely to take place, especially in the beginning.  
- You usually need more than 1 single space  
- Low growth factor and low initial reserved size means small sizes in the beginning (1, 2, 4, 8 ...), even though it grows fast later on

☘ Assuming the growth factor is 2, the average cost of inserting a new element is **3**, which is reasonably high.  
- Use your favorite complexity analysis method: Aggregation, Accounting, Potential ... etc., any will do  
- The average cost for `lni::vector` is **2.333**, and is in fact lower for the reason stated below

☘ The impact of growth factors is underestimated.  
- In these analyses, we "falsely" assume that a memory reallocation would be the last operation
- The actual average cost is in fact lower, because the costs for the elements inserted after the last memory reallocation are essentially FREE

### The correct way to use your vector

☘ If you still want to use STLs,  
**ALWAYS reserve a reasonable size** before you start inserting elements.

☘ A better way in my opinion, is to:   
**Use an implementation with a high growth factor** like mine,  
and **use `shrink_to_fit()` remove redundancies after you've completed inserting all the elements**.  
This is because you don't always know how much space you need (Sometimes it depends on the input),  
and over-reserving isn't always a good thing.


## License

[![Creative Commons Attribution 4.0 International](https://i.creativecommons.org/l/by/4.0/88x31.png)](http://creativecommons.org/licenses/by/4.0/)

`lni::vector` by Jasmine "lnishan" Chen is licensed under a [Creative Commons Attribution 4.0 International License](http://creativecommons.org/licenses/by/4.0/).
