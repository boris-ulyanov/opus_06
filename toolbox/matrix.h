/**
 * @brief Sparce matrix module
 */

#pragma once

#include <assert.h>
#include <array>
#include <iostream>
#include <map>

namespace matrix {

using idx_type = uint32_t;

template <typename T, T default_value, uint8_t dimension = 2>
class Matrix {
    static_assert(dimension > 0);

    using key_type = typename std::array<idx_type, dimension>;
    using stor_type = typename std::map<key_type, T>;
    using value_type = typename stor_type::value_type;

    stor_type stor;

    T get(const key_type& key) const {
        const auto& iter = stor.find(key);
        if (iter == stor.end()) return default_value;
        return iter->second;
    }

    void set(const key_type& key, T value) {
        if (value == default_value)
            stor.erase(key);
        else
            stor[key] = value;
    }

    // for access over operator()
    struct Locator {
        Matrix& owner;
        key_type key;

        template <typename... Indexes>
        Locator(Matrix& _owner, Indexes... _indexes) : owner(_owner) {
            key = {static_cast<idx_type>(_indexes)...};
        }

        operator T() const {
            return owner.get(key);
        }

        T operator=(const T& value) {
            owner.set(key, value);
            return value;
        }
    };

    // for access over operator[]
    struct Locator2 {
        Matrix& owner;
        key_type key;
        std::size_t key_size;

        Locator2(Matrix& _owner, const idx_type index) : owner(_owner), key_size(1) {
            key[0] = index;
        }

        Locator2& operator[](const idx_type index) {
            assert(key_size < dimension);
            key[key_size] = index;
            ++key_size;
            return *this;
        }

        operator T() const {
            assert(key_size == dimension);
            return owner.get(key);
        }

        T operator=(const T& value) {
            assert(key_size == dimension);
            owner.set(key, value);
            return value;
        }
    };

    class iterator {
        // using value_type = typename stor_type::value_type;
        typename stor_type::iterator current;

       public:
        explicit iterator(typename stor_type::iterator current_) : current(current_){};

        auto operator!=(const iterator& rhs) const {
            return current != rhs.current;
        }

        auto& operator++() {
            ++current;
            return *this;
        }

        // const auto& operator*() {
        const value_type& operator*() {
            return *current;
        }
    };

   public:
    std::size_t size() {
        return stor.size();
    }

    template <typename... Indexes>
    Locator& operator()(Indexes... indexes) {
        static_assert((sizeof...(Indexes)) == dimension);
        auto locator = new Locator{*this, indexes...};
        return *locator;
    }

    Locator2& operator[](const idx_type index) {
        auto locator = new Locator2{*this, index};
        return *locator;
    }

    auto begin() {
        return *(new iterator(stor.begin()));
    }

    auto end() {
        return *(new iterator(stor.end()));
    }
};
}
