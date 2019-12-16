/**
 * @brief is_container helper module
 */

#pragma once

#include <map>

template <typename T, T default_value, uint8_t dimensions = 2>
class Matrix {
    int a;

public:
    std::size_t size() {return 0;}

    int operator()(uint32_t i, uint32_t j) {return 0;}
};
