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

To use the provided main file:

```bash
    > g++ main.cpp -std=c++20 -o my_hll
    > python3 gen_data.py <number of values to generate>
    > ./my_hll < data.txt
```