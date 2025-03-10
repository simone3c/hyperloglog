# Hyperloglog
Simple single-file C++ implementation of the Hyperloglog data structure

# Basic usage
```cpp
#include "hll.hpp"

int main(){

    // 10 bits are used for buckets
    Hll my_hll = Hll<10>();

    my_hll.insert(1);
    my_hll.insert(2);
    // ...

    // estimate of unique inserted elements
    double estimate = my_hll.count_unique();
}
```