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
    using data_iter = typename data_type::iterator;
    using data_const_iter = typename data_type::const_iterator;

    data_type data;

   public:
    class Iterator {
        data_const_iter current;
        typename value_type::slice_iter child;

       public:
        explicit Iterator(data_const_iter current_)
            : current(current_), child((*current_).second.begin()){};

        auto operator=(const Iterator& rhs) {
            current = rhs.current;
            child = rhs.child;
        }

        auto operator!=(const Iterator& rhs) const {
            return current != rhs.current;
        }

        auto& operator++() {
            ++child;
            if (child != (*current).second.end()) return *this;
            ++current;
            child = (*current).second.begin();  // dereference end???
            return *this;
        }

        auto operator*() const {
            return *current;
        }

        void get_addr_value(key_type* addr, T* value) const {
            *addr = (*current).first;
            ++addr;
            if constexpr(deep_level > 2) {
                child.get_addr_value(addr, value);
            } else {
                *addr = (*child).first;
                *value = (*child).second;
            }
        }
    };

   public:
    using slice_iter = Iterator;

    std::size_t size() const {
        std::size_t s = 0;
        for (const auto a : data) s += a.second.size();
        return s;
    }

    T get(const key_type* index) const {
        data_const_iter iter = data.find(*index);
        if (iter == data.end()) return default_value;
        return iter->second.get(++index);
    }

    void set(T value, const key_type* index) {
        auto& sub_slice = data[*index];
        sub_slice.set(value, ++index);
    }

    void rm(const key_type* index) {
        data_iter iter = data.find(*index);
        if (iter == data.end()) return;
        iter->second.rm(++index);
        if (iter->second.size() == 0) {
            data.erase(iter);
        }
    }

    auto begin() const noexcept {
        return *(new Iterator(data.begin()));
    }

    auto end() const noexcept {
        return *(new Iterator(data.end()));
    }
};

template <typename T, T default_value>
class Slice<T, default_value, 1> {
    using data_type = typename std::map<key_type, T>;
    data_type data;

   public:
    using slice_iter = typename data_type::const_iterator;

    std::size_t size() const {
        return data.size();
    }

    T get(const key_type* index) const {
        slice_iter iter = data.find(*index);
        if (iter == data.end()) return default_value;
        return iter->second;
    }

    void set(T value, const key_type* index) {
        data[*index] = value;
    }

    void rm(const key_type* index) {
        data.erase(*index);
    }

    auto begin() const noexcept {
        return data.begin();
    }

    auto end() const noexcept {
        return data.end();
    }
};
}
