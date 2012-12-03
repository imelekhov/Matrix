#ifndef _MATRIX_COLUMNMATRIX_H
#define _MATRIX_COLUMNMATRIX_H

#include <GenericMatrix.h>
#include "algorithms.h"

namespace Matrix {

/*! \class ColumnMatrix
  \brief Шаблон ColumnMatrix - класс реализации общих математических операций с матрицами-столбцами
  \tparam T - тип элементов матрицы
  \tparam n - количество строк матрицы
*/
template<typename T, int n>
class ColumnMatrix : public GenericMatrix<T, n, 1> {
protected:
    using GenericMatrix<T, n, 1>::m_array;
public:
/*!
  конструктор по умолчанию
*/
    ColumnMatrix (void) : GenericMatrix<T, n, 1>() {
    }

/*!
  конструктор копирования
  \param other - копируемая матрица
*/
    ColumnMatrix (const ColumnMatrix<T, n>& other) : GenericMatrix<T, n, 1>(other) {
    }

/*!
  конструктор копирования
  \param other - копируемая матрица
*/
    ColumnMatrix (const GenericMatrix<T, n, 1>& other) : GenericMatrix<T, n, 1>(other) {
    }

/*!
  конструктор из литерала нулевой матрицы
*/
    ColumnMatrix (null_t literal) : GenericMatrix<T, n, 1>(literal) {
    }

/*!
  конструктор из списка инициализации
  \param list - список инициализации
*/
    ColumnMatrix (const std::initializer_list<T>& list) {
        algorithms::cp(this->array(), list, n);
    }

/*!
  оператор индексации
  \param row - индекс строки матрицы
  \return константная ссылка на элемент в массиве элементов матрицы
*/
    const T& operator[] (int row) const {
        return m_array[row][0];
    }

/*!
  оператор индексации
  \param row - индекс строки матрицы
  \return ссылка на элемент в массиве элементов матрицы
*/
    T& operator[] (int row) {
        return m_array[row][0];
    }
};

}

#endif
