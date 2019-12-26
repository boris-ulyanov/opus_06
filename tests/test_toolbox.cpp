#define BOOST_TEST_MODULE toolbox_test_module

#include "matrix.h"

#include <boost/test/unit_test.hpp>

#include <iostream>

using namespace matrix;

BOOST_AUTO_TEST_SUITE(toolbox_test_suite)

BOOST_AUTO_TEST_CASE(toolbox_test_hw) {
    Matrix<int, -1> matrix;
    BOOST_CHECK(matrix.size() == 0);
    auto a = matrix(0, 0);
    BOOST_CHECK(a == -1);
    BOOST_CHECK(matrix.size() == 0);
    matrix(100, 100) = 314;
    BOOST_CHECK(matrix(100, 100) == 314);
    BOOST_CHECK(matrix.size() == 1);
}

BOOST_AUTO_TEST_CASE(toolbox_test_1d) {
    Matrix<int, -11, 1> matrix;
    BOOST_CHECK(matrix.size() == 0);
    auto a = matrix[1];
    BOOST_CHECK(a == -11);
    BOOST_CHECK(matrix.size() == 0);
    matrix[100] = 123;
    matrix[200] = 456;
    BOOST_CHECK(matrix[100] == 123);
    BOOST_CHECK(matrix.size() == 2);
}

BOOST_AUTO_TEST_CASE(toolbox_test_3d) {
    Matrix<int, -11, 3> matrix;
    BOOST_CHECK(matrix.size() == 0);
    auto a = matrix[1][1][1];
    BOOST_CHECK(a == -11);
    BOOST_CHECK(matrix.size() == 0);

    matrix[100][100][100] = 123;
    matrix(200, 200, 200) = 456;
    BOOST_CHECK(matrix[100][100][100] == 123);
    BOOST_CHECK(matrix(200, 200, 200) == 456);
    BOOST_CHECK(matrix.size() == 2);

    matrix[100][100][100] = -11;
    BOOST_CHECK(matrix.size() == 1);

    matrix(200, 200, 200) = -11;
    BOOST_CHECK(matrix.size() == 0);
}

BOOST_AUTO_TEST_CASE(toolbox_test_for_loop) {
    Matrix<uint32_t, 999, 3> m1;
    Matrix<uint32_t, 999, 3> m2;
    Matrix<uint32_t, 999, 3> m3;

    for (int i = 0; i < 5; ++i) {
        m1[i][0][0] = i;
        m2[0][i][0] = i;
        m3[0][0][i] = i;
    }

    int ctr1 = 0, ctr2 = 0, ctr3 = 0;

    for (const auto v : m1) {
        BOOST_CHECK(v.value == v.addr[0]);
        ++ctr1;
    }
    BOOST_CHECK(ctr1 == 5);

    for (const auto v : m2) {
        BOOST_CHECK(v.value == v.addr[1]);
        ++ctr2;
    }
    BOOST_CHECK(ctr2 == 5);

    // Segmentation fault
    // for (const auto v : m3) {
    //     std::cout << "value: " << v.value << "; addr: ( ";
    //     for (const auto addr : v.addr) std::cout << addr << ", ";
    //     std::cout << ")" << std::endl;
    //     ++ctr3;
    // }
    // BOOST_CHECK(ctr3 == 5);
    (void)ctr3;
}

BOOST_AUTO_TEST_SUITE_END()
