#ifndef MY_HLL_
#define MY_HLL_

#include <cstdint>
#include <cmath>
#include <functional>
#include <cassert>
#include <algorithm>

/**
 * Simple implementation of Hyperloglog data structure
 *
 * This implementation is based on the article:
 * https://algo.inria.fr/flajolet/Publications/FlFuGaMe07.pdf
 *
 */

template<uint8_t P>
class Hll{
    // number of bits used to encode the bucket's index
    const uint8_t p = P;
    // total number of buckets available
    const uint32_t m = 1 << P;

    std::array<uint32_t, 1 << P> buckets;

    // simple hash function to be used if the user doesn't provide another one
    static constexpr auto default_hash = [](uint32_t x){
        x ^= x >> 16;
        x *= 0x85ebca6bU;
        x ^= x >> 13;
        x *= 0xc2b2ae35U;
        x ^= x >> 16;
        return x;
    };

    // see the paper for alpha's definition
    inline static constexpr double alpha(){
        switch (1 << P){
        case 16:
            return 0.673;

        case 32:
            return 0.697;

        case 64:
            return 0.709;

        default:
            return 0.7213 / (1 + 1.079 / (1 << P));
        }
    }

    std::function<uint32_t(uint32_t)> hash;

public:

    Hll(): Hll(Hll::default_hash) {}

    Hll(const std::function<uint32_t(uint32_t)>& h): hash(h){
        // practical limitation added in the original paper
        static_assert(P >= 4 && P <= 16);

        this->buckets.fill(0);
    }

    double count_unique() const{

        double estimate, count = 0;

        for(uint32_t i = 0; i < this->m; ++i){
            count += 1. / (1 << this->buckets[i]);
        }
        count = Hll::alpha() * this->m * this->m / count;

        if(count <= 2.5 * this->m){
            int empty = std::count(this->buckets.begin(), this->buckets.end(), 0);
            estimate = empty ?
                this->m * std::log10(this->m / static_cast<double>(empty)) :
                count;
        }

        else if(count <= (1L << 32) / 30.){
            estimate = count;
        }

        else{
            estimate = -(1L << 32) * log10(1 - count / (1L << 32));
        }

        return estimate;
    };

    void insert(uint32_t e){

        uint32_t x = hash(e);

        uint32_t idx = x >> (8 * sizeof(uint32_t) - this->p);

        uint32_t w = x & ~(idx << (8 * sizeof(uint32_t) - this->p));

        this->buckets[idx] = std::max<uint32_t>(
            this->buckets[idx],
            __builtin_clz(w) - this->p + 1
        );
    };

    void reset(){
        this->buckets.fill(0);
    }
};

#endif