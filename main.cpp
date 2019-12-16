
#include "matrix.h"

#include <assert.h>

int main() {

	Matrix<int, -1> matrix; // бесконечная матрица int заполнена значениями -1
	assert(matrix.size() == 0); // все ячейки свободны
	auto a = matrix(0, 0);
	assert(a == -1);
	assert(matrix.size() == 0);
	// matrix(100, 100) = 314;
	assert(matrix(100, 100) == 314);
	assert(matrix.size() == 1);

    return 0;
}
