/**
 * @brief Sparce matrix module
 */

#pragma once

#include "slice.h"

#include <array>

namespace matrix {

template <typename T, T default_value, uint8_t dimension = 2>
class Matrix {
    using key_type = uint32_t;

    static_assert(dimension > 0);

    using data_type = Slice<T, default_value, dimension>;
    data_type data;

    struct Locator {
        Matrix* owner;
        std::array<key_type, dimension> indexes;

        template <typename... Indexes>
        Locator(Matrix* _matrix, Indexes... _indexes) : owner(_matrix) {
            indexes = {static_cast<key_type>(_indexes)...};
        }

        operator T() const {
            return owner->data.get(indexes.data());
        }

        T operator=(const T& value) {
            owner->data.set(value, indexes.data());
            return value;
        }
    };

   public:
    std::size_t size() {
        return data.size();
    }

    template <typename... Indexes>
    Locator& operator()(Indexes... indexes) {
        static_assert((sizeof...(Indexes)) == dimension);
        auto locator = new Locator{this, indexes...};
        return *locator;
    }
};
}
