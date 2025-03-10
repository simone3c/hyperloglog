#include <iostream>

#include "hll.hpp"

int main(){

    Hll h4 = Hll<8>();

    uint32_t len, unique, n;
    std::cin >> len;
    std::cin >> unique;
    while (len--){
        std::cin >> n;
        h4.insert(n);
    }

    double est = h4.count_unique();
    std::cout << "Actual unique elements: " << unique << "\n";
    std::cout << "Estimated unique elements: " << est << "\n";
    std::cout << "Realtive error: " << std::fabs(est - unique) / unique * 100 << "%\n";

}

