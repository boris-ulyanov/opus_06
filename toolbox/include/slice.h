/**
 * @brief Sparce matrix slice module
 */

#pragma once

#include <assert.h>
#include <map>

namespace matrix {

using key_type = uint32_t;

template <typename T, T default_value, uint8_t deep_level>
class Slice {
    using value_type = Slice<T, default_value, deep_level - 1>;
    using data_type = typename std::map<key_type, value_type>;
    using const_iterator = typename data_type::const_iterator;

    data_type data;

    class iterator {
        const_iterator current;
        typename value_type::const_iterator child;

       public:
        explicit iterator(const_iterator current_)
            : current(current_), child((*current_).second.begin()){};

        auto operator!=(const iterator& rhs) const {
            return current != rhs.current;
        };

        auto& operator++() {
            child++;
            if (child == (*current).second.end()) {
                current++;
                assert((*current).second.size() > 0);  // empty nodes break everything
                child = (*current).second.begin();     // dereference end???
            }
            return *this;
        };

        auto operator*() const {
            return *current;
        };
    };

   public:
    std::size_t size() const {
        std::size_t s = 0;
        for (const auto a : data) s += a.second.size();
        return s;
    }

    T get(const key_type* index) const {
        const_iterator iter = data.find(*index);
        if (iter == data.end()) return default_value;
        return iter->second.get(++index);
    }

    void set(T value, const key_type* index) {
        auto& sub_slice = data[*index];
        sub_slice.set(value, ++index);
    }

    auto begin() const noexcept {
        return *(new iterator(data.begin()));
    }

    auto end() const noexcept {
        return *(new iterator(data.end()));
    }
};

template <typename T, T default_value>
class Slice<T, default_value, 1> {
    using data_type = typename std::map<key_type, T>;
    data_type data;

   public:
    using const_iterator = typename data_type::const_iterator;

    std::size_t size() const {
        return data.size();
    }

    T get(const key_type* index) const {
        const_iterator iter = data.find(*index);
        if (iter == data.end()) return default_value;
        return iter->second;
    }

    void set(T value, const key_type* index) {
        data.insert_or_assign(*index, value);
    }

    auto begin() const noexcept {
        return data.begin();
    }

    auto end() const noexcept {
        return data.end();
    }
};
}
