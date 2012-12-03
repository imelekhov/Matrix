#ifndef _MATRIX_CONJUGATE_H
#define _MATRIX_CONJUGATE_H

#include <GenericMatrix.h>
#include <SquareMatrix.h>
#include <transpose.h>

namespace Matrix {

/*!
  сопряжение квадратной матрицы другой матрицей
  \tparam n - количество строк и столбцов в результирующей матрице
  \tparam m - количество строк и столбцов в исходной матрице
  \param M - сопрягаемая квадратная матрица \a m x \a m
  \param C - сопрягающая матрица \a n x \a m
  \return \a M, умноженная слева на \a C и справа на транспонированную \a C
*/
template<typename T, int n, int m>
const SquareMatrix<T, n> conjugate (const SquareMatrix<T, m>& M, const GenericMatrix<T, n, m>& C) {
    return C * M * transpose(C);
}

/*!
  транспонированное сопряжение квадратной матрицы другой матрицей
  \tparam n - количество строк и столбцов в результирующей матрице
  \tparam m - количество строк и столбцов в исходной матрице
  \param M - сопрягаемая квадратная матрица \a m x \a m
  \param C - сопрягающая матрица \a m x \a n
  \return \a M, умноженная слева на транспонированную \a C и справа на \a C
*/
template<typename T, int n, int m>
const SquareMatrix<T, n> conjugate_transposed (const SquareMatrix<T, m>& M, const GenericMatrix<T, m, n>& C) {
    return transpose(C) * M * C;
}

}

#endif
