#define BOOST_TEST_MODULE toolbox_test_module

#include "matrix.h"

#include <boost/test/unit_test.hpp>

using namespace matrix;

BOOST_AUTO_TEST_SUITE(toolbox_test_suite)

BOOST_AUTO_TEST_CASE(toolbox_test_hw) {
    Matrix<int, -1> matrix;
    assert(matrix.size() == 0);
    auto a = matrix(0, 0);
    BOOST_CHECK(a == -1);
    BOOST_CHECK(matrix.size() == 0);
    matrix(100, 100) = 314;
    BOOST_CHECK(matrix(100, 100) == 314);
    BOOST_CHECK(matrix.size() == 1);
}

BOOST_AUTO_TEST_CASE(toolbox_test_1d) {
    Matrix<int, -11, 1> matrix;
    assert(matrix.size() == 0);
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
    assert(matrix.size() == 0);
    auto a = matrix[1][1][1];
    BOOST_CHECK(a == -11);
    BOOST_CHECK(matrix.size() == 0);
    matrix[100][100][100] = 123;
    matrix[200][200][200] = 456;
    BOOST_CHECK(matrix[100][100][100] == 123);
    BOOST_CHECK(matrix.size() == 2);
}


BOOST_AUTO_TEST_SUITE_END()
