
#include "matrix.h"

#include <assert.h>
#include <iostream>

int main() {
    using namespace matrix;

    const int N = 10;
    const int default_value = 0;

    Matrix<int, default_value> m;

    for (int i = 0; i < 10; ++i) {
        m[i][i] = m[N - 1 - i][i] = i;
    }

    for (int i = 0; i < 10; i += 2) {
        for (int j = 0; j < 10; j += 2) {
            m[i][j] = m[i + 1][j + 1] = default_value;
        }
    }

    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << m.size() << std::endl;

    for (const auto v : m) {
        std::cout << (v).first << std::endl;
    }

    return 0;
}
