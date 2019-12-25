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
        Matrix* owner;
        std::array<key_type, dimension> indexes;

        template <typename... Indexes>
        Locator(Matrix* _matrix, Indexes... _indexes) : owner(_matrix) {
            indexes = {static_cast<key_type>(_indexes)...};
        }

        operator T() const {
            return owner->root_slice.get(indexes.data());
        }

        T operator=(const T& value) {
            if (value == default_value)
                owner->root_slice.rm(indexes.data());
            else
                owner->root_slice.set(value, indexes.data());
            return value;
        }
    };

    // for access over operator[]
    struct Locator2 {
        Matrix* owner;
        std::array<key_type, dimension> indexes;
        std::size_t size;

        Locator2(Matrix* _matrix, const key_type index) : owner(_matrix), size(0) {
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
            return owner->root_slice.get(indexes.data());
        }

        T operator=(const T& value) {
            assert(size == dimension);
            if (value == default_value)
                owner->root_slice.rm(indexes.data());
            else
                owner->root_slice.set(value, indexes.data());
            return value;
        }
    };

   public:
    std::size_t size() {
        return root_slice.size();
    }

    template <typename... Indexes>
    Locator& operator()(Indexes... indexes) {
        static_assert((sizeof...(Indexes)) == dimension);
        auto locator = new Locator{this, indexes...};
        return *locator;
    }

    Locator2& operator[](const key_type index) {
        auto locator = new Locator2{this, index};
        return *locator;
    }

    auto begin() {
        return root_slice.begin();
    }

    auto end() {
        return root_slice.end();
    }
};
}
