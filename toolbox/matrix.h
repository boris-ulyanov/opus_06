/**
 * @brief Sparce matrix module
 */

#pragma once

#include "slice.h"

#include <assert.h>
#include <array>

namespace matrix {

template <typename T, T default_value, uint8_t dimension = 2>
class Matrix {
    using key_type = uint32_t;

    static_assert(dimension > 0);

    using root_slice_type = Slice<T, default_value, dimension>;
    root_slice_type root_slice;

    // for access over operator()
    struct Locator {
        root_slice_type& root_slice;
        std::array<key_type, dimension> indexes;

        template <typename... Indexes>
        Locator(root_slice_type& _root_slice, Indexes... _indexes) : root_slice(_root_slice) {
            indexes = {static_cast<key_type>(_indexes)...};
        }

        operator T() const {
            return root_slice.get(indexes.data());
        }

        T operator=(const T& value) {
            if (value == default_value)
                root_slice.rm(indexes.data());
            else
                root_slice.set(value, indexes.data());
            return value;
        }
    };

    // for access over operator[]
    struct Locator2 {
        root_slice_type& root_slice;
        std::array<key_type, dimension> indexes;
        std::size_t size;

        Locator2(root_slice_type& _root_slice, const key_type index)
            : root_slice(_root_slice), size(0) {
            indexes[0] = index;
            ++size;
        }

        Locator2& operator[](const key_type index) {
            assert(size < dimension);
            indexes[size] = index;
            ++size;
            return *this;
        }

        operator T() const {
            assert(size == dimension);
            return root_slice.get(indexes.data());
        }

        T operator=(const T& value) {
            assert(size == dimension);
            if (value == default_value)
                root_slice.rm(indexes.data());
            else
                root_slice.set(value, indexes.data());
            return value;
        }
    };

    class Iterator {
        using root_slice_iter = typename root_slice_type::slice_iter;
        root_slice_iter current;

       public:
        std::array<key_type, dimension> addr;
        T value;

        explicit Iterator(root_slice_iter current_) : current(current_) {};

        auto operator!=(const Iterator& rhs) const {
            return current != rhs.current;
        }

        auto& operator++() {
            ++current;
            return *this;
        }

        Iterator& operator*() {
            current.get_addr_value(addr.data(), &value);
            return *this;
        }
    };

   public:
    std::size_t size() {
        return root_slice.size();
    }

    template <typename... Indexes>
    Locator& operator()(Indexes... indexes) {
        static_assert((sizeof...(Indexes)) == dimension);
        auto locator = new Locator{root_slice, indexes...};
        return *locator;
    }

    Locator2& operator[](const key_type index) {
        auto locator = new Locator2{root_slice, index};
        return *locator;
    }

    auto& begin() {
        return *(new Iterator(root_slice.begin()));
    }

    auto& end() {
        return *(new Iterator(root_slice.end()));
    }
};
}
