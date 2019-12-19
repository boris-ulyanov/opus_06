/**
 * @brief is_container helper module
 */

#pragma once

#include <map>

using index = uint32_t;

template <typename T, T default_value, uint8_t deep_level>
class DataSlice {
    using mapped_type = DataSlice<T, default_value, deep_level - 1>;
    using data_type = std::map<index, mapped_type>;
    data_type data;

   public:
    std::size_t size() const {
        std::size_t s = 0;
        for (const auto a : data) s += a.second.size();
        return s;
    }
};

template <typename T, T default_value>
class DataSlice<T, default_value, 0> {
    using data_type = std::map<index, T>;
    data_type data;

   public:
    std::size_t size() const {
        return data.size();
    }
};

// ==================

template <typename T, T default_value, uint8_t dimension = 2>
class Matrix {
    static_assert(dimension > 0);

    using data_type = DataSlice<T, default_value, dimension - 1>;

    data_type data;

   public:
    std::size_t size() {
        return data.size();
    }

    int operator()(index i, index j) {
        return 0;
    }
};
