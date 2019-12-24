/**
 * @brief Sparce matrix slice module
 */

#pragma once

#include <map>

namespace matrix {

using key_type = uint32_t;

template <typename T, T default_value, uint8_t deep_level>
class Slice {
    using value_type = Slice<T, default_value, deep_level - 1>;
    using data_type = typename std::map<key_type, value_type>;
    using iter_type = typename data_type::const_iterator;

    data_type data;

   public:
    std::size_t size() const {
        std::size_t s = 0;
        for (const auto a : data) s += a.second.size();
        return s;
    }

    T get(const key_type* index) const {
        iter_type iter = data.find(*index);
        if (iter == data.end()) return default_value;
        return iter->second.get(++index);
    }

    void set(T value, const key_type* index) {
        auto& sub_slice = data[*index];
        sub_slice.set(value, ++index);
    }
};

template <typename T, T default_value>
class Slice<T, default_value, 1> {
    using data_type = typename std::map<key_type, T>;
    using iter_type = typename data_type::const_iterator;
    data_type data;

   public:
    std::size_t size() const {
        return data.size();
    }

    T get(const key_type* index) const {
        iter_type iter = data.find(*index);
        if (iter == data.end()) return default_value;
        return iter->second;
    }

    void set(T value, const key_type* index) {
        data.insert_or_assign(*index, value);
    }
};
}
