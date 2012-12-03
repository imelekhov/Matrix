#ifndef _MATRIX_TRANSPOSE_H
#define _MATRIX_TRANSPOSE_H

#include <GenericMatrix.h>
#include <SquareMatrix.h>
#include <ColumnMatrix.h>
#include <RowMatrix.h>
#include "algorithms.h"

namespace Matrix {

/*! \relates GenericMatrix
  транспонирование матрицы
  \tparam n - количество строк исходной матрицы
  \tparam m - количество столбцов исходной матрицы
  \param M - матрица \a n x \a m
  \return матрица \a m x \a n - транспонированная \a M
*/
template<typename T, int n, int m>
const GenericMatrix<T, m, n> transpose (const GenericMatrix<T, n, m>& M) {
    GenericMatrix<T, m, n> R;
    algorithms::transpose(R.array(), M.array(), n, m);
    return R;
}

/*! \relates SquareMatrix
  транспонирование квадратной матрицы
  \param M - квадратная матрица
  \return квадратная матрица - транспонированная \a M
*/
template<typename T, int n>
const SquareMatrix<T, n> transpose (const SquareMatrix<T, n>& M) {
    return transpose((const GenericMatrix<T, n, n>&) M);
}

/*! \relates ColumnMatrix
  транспонирование матрицы-столбца
  \param M - матрица-столбец
  \return матрица-строка - транспонированная \a M
*/
template<typename T, int n>
const RowMatrix<T, n> transpose (const ColumnMatrix<T, n>& M) {
    return transpose((const GenericMatrix<T, n, 1>&) M);
}

/*! \relates RowMatrix
  транспонирование матрицы-строки
  \param M - матрица-строка
  \return матрица-столбец - транспонированная \a M
*/
template<typename T, int n>
const ColumnMatrix<T, n> transpose (const RowMatrix<T, n>& M) {
    return transpose((const GenericMatrix<T, 1, n>&) M);
}

}

#endif
