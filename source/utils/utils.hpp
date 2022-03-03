#ifndef UTILS
#define UTILS

#include <vector>
#include <iostream>

namespace utils {

    template<typename T>
    std::vector<T> slice(std::vector<T> v, int start, int end) {
        std::vector<T> vec((uint64_t)end - (uint64_t)start + 1);
        std::copy(v.begin() + start, v.begin() + end + 1, vec.begin());
        return vec;
    }

    template<typename T>
    T value_from_vector(std::vector<char> v) {
        T value = 0x0;
        for (size_t i = 0; i < sizeof(T); i++)
            value = value | (uint8_t)v.at(i) << 8 * i;
        return value;
    }

    int inverse_index(int idx);

}

#endif // !UTILS
