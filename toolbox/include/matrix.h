/**
 * @brief is_container helper module
 */

#pragma once

#include "slice.h"

namespace matrix {

template <typename T, T default_value, uint8_t dimension = 2>
class Matrix {
    using key_type = uint32_t;

    static_assert(dimension > 0);

    using data_type = Slice<T, default_value, dimension>;
    data_type data;

   public:
    std::size_t size() {
        return data.size();
    }

    template <typename... Indexes>
    const T get(Indexes... indexes) const {
        static_assert((sizeof...(Indexes)) == dimension);
        return data.get(indexes...);
    }

    template <typename... Indexes>
    void set(T value, Indexes... indexes) {
        static_assert((sizeof...(Indexes)) == dimension);
        data.set(value, indexes...);
    }

    int operator()(key_type i, key_type j) {  // FixIt
        return 0;
    }
};
}
