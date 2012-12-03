#ifndef _MATRIX_DOT_H
#define _MATRIX_DOT_H

#include <ColumnMatrix.h>
#include <RowMatrix.h>
#include "algorithms.h"

namespace Matrix {

/*! \relates ColumnMatrix
  скалярное произведение матриц-столбцов
  \param lhs - первый множитель
  \param rhs - второй множитель
  \return скалярное произведение \a lhs и \a rhs
*/
template<typename T, int n>
T dot (const ColumnMatrix<T, n>& lhs, const ColumnMatrix<T, n>& rhs) {
    return algorithms::dot(lhs.array(), rhs.array(), n);
}

/*! \relates RowMatrix
  скалярное произведение матриц-строк
  \param lhs - первый множитель
  \param rhs - второй множитель
  \return скалярное произведение \a lhs и \a rhs
*/
template<typename T, int n>
T dot (const RowMatrix<T, n>& lhs, const RowMatrix<T, n>& rhs) {
    return algorithms::dot(lhs.array(), rhs.array(), n);
}

}

#endif
