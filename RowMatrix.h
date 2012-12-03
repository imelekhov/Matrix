#ifndef _MATRIX_ROWMATRIX_H
#define _MATRIX_ROWMATRIX_H

#include <GenericMatrix.h>
#include "algorithms.h"

namespace Matrix {

/*! \class RowMatrix
  \brief Шаблон RowMatrix - класс реализации общих математических операций с матрицами-строками
  \tparam T - тип элементов матрицы
  \tparam n - количество строк матрицы
*/
template<typename T, int n>
class RowMatrix : public GenericMatrix<T, 1, n> {
protected:
    using GenericMatrix<T, 1, n>::m_array;
public:
/*!
  конструктор по умолчанию
*/
    RowMatrix (void) : GenericMatrix<T, 1, n>() {
    }

/*!
  конструктор копирования
  \param other - копируемая матрица
*/
    RowMatrix (const RowMatrix<T, n>& other) : GenericMatrix<T, 1, n>(other) {
    }

/*!
  конструктор копирования
  \param other - копируемая матрица
*/
    RowMatrix (const GenericMatrix<T, 1, n>& other) : GenericMatrix<T, 1, n>(other) {
    }

/*!
  конструктор из литерала нулевой матрицы
*/
    RowMatrix (null_t literal) : GenericMatrix<T, 1, n>(literal) {
    }

/*!
  конструктор из списка инициализации
  \param list - список инициализации
*/
    RowMatrix (const std::initializer_list<T>& list) {
        algorithms::cp(this->array(), list, n);
    }

/*!
  оператор индексации
  \param column - индекс столбца матрицы
  \return константная ссылка на элемент в массиве элементов матрицы
*/
    const T& operator[] (int column) const {
        return m_array[0][column];
    }

/*!
  оператор индексации
  \param column - индекс столбца матрицы
  \return ссылка на элемент в массиве элементов матрицы
*/
    T& operator[] (int column) {
        return m_array[0][column];
    }
};

}

#endif
