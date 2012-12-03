#ifndef _MATRIX_SQR_H
#define _MATRIX_SQR_H

#include <ColumnMatrix.h>
#include <RowMatrix.h>
#include <SquareMatrix.h>
#include <transpose.h>

namespace Matrix {

/*! \relates ColumnMatrix
  произведение матрицы-столбца на себя
  \param v - матрица-столбец
  \return квадратная матрица, равная произведению \a v на транспонированную \a v
*/
template<typename T, int n>
const SquareMatrix<T, n> sqr (const ColumnMatrix<T, n>& v) {
    return v * transpose(v);
}

/*! \relates RowMatrix
  произведение матрицы-строки на себя
  \param v - матрица-строка
  \return квадратная матрица, равная произведению транспонированной \a v на \a v
*/
template<typename T, int n>
const SquareMatrix<T, n> sqr (const RowMatrix<T, n>& v) {
    return transpose(v) * v;
}

}

#endif
