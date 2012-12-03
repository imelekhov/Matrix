#ifndef _MATRIX_SQUAREMATRIX_H
#define _MATRIX_SQUAREMATRIX_H

#include <GenericMatrix.h>
#include <identity_t.h>
#include "algorithms.h"

namespace Matrix {

/*! \class SquareMatrix
  \brief Шаблон SquareMatrix - класс реализации общих математических операций с квадратными матрицами
  \tparam T - тип элементов матрицы
  \tparam n - количество строк и столбцов матрицы
*/
template<typename T, int n>
class SquareMatrix : public GenericMatrix<T, n, n> {
public:
    using GenericMatrix<T, n, n>::operator *=;

/*!
  конструктор по умолчанию
*/
    SquareMatrix (void) : GenericMatrix<T, n, n>() {
    }

/*!
  конструктор копирования
  \param other - копируемая матрица
*/
    SquareMatrix (const SquareMatrix& other) : GenericMatrix<T, n, n>(other) {
    }

/*!
  конструктор копирования
  \param other - копируемая матрица
*/
    SquareMatrix (const GenericMatrix<T, n, n>& other) : GenericMatrix<T, n, n>(other) {
    }

/*!
  конструктор из литерала нулевой матрицы
*/
    SquareMatrix (null_t literal) : GenericMatrix<T, n, n>(literal) {
    }

/*!
  конструктор из литерала единичной матрицы
*/
    SquareMatrix (identity_t) : GenericMatrix<T, n, n>() {
        algorithms::identity(this->array(), n);
    }

/*!
  конструктор из списка инициализации
  \param list - список инициализации
*/
    SquareMatrix (const std::initializer_list<std::initializer_list<T>>& list) : GenericMatrix<T, n, n>(list) {
    }

/*!
  оператор присваивания матрице значения единичной матрицы
*/
    SquareMatrix& operator = (identity_t) {
        algorithms::identity(this->array(), n);
        return *this;
    }

/*!
  оператор умножения справа на другую матрицу
  \param other - другая матрица
  \return матрица, умноженная справа на \a other
*/
    SquareMatrix& operator *= (const SquareMatrix& other) {
        return *this = *this * other;
    }

/*!
  одновременное вычисление определителя и обратной матрицы (в случае ненулевого определителя)
  \param inverse - ссылка на матрицу, которая будет приравнена к обратной (не поменяется в случае нулевого определителя)
  \return определитель матрицы
*/
    T det (SquareMatrix<T, n>&) const;

/*!
  диагональная матрица
  \param array - массив диагональных элементов
  \return диагональная матрица с заданными элементами
*/
    static const SquareMatrix diag (const T array[]);

/*!
  матрица транспозиции
  \param i - индекс первой строки и первого столбца матрицы транспозиции
  \param j - индекс второй строки и второго столбца матрицы транспозиции
  \return единичная матрица, в которой единицы на позициях (\a i, \a i) и (\a j, \a j) заменены на единицы в позициях (\a i, \a j) и (\a j, \a i)
*/
    static const SquareMatrix transposition (int i, int j);
};

template<typename T, int n>
T SquareMatrix<T, n>::det (SquareMatrix<T, n>& inverse) const {
    SquareMatrix<T, n> E = identity;
    GenericMatrix<T, n, 2 * n> C = cat(E, *this);
    T D = algorithms::gauss(C.array(), n);
    inverse = minor<T, n, 2 * n, n, n>(C);
    return D;
}

template<typename T, int n>
const SquareMatrix<T, n> SquareMatrix<T, n>::diag (const T array[]) {
    SquareMatrix E;
    algorithms::diag(E.array(), array, n);
    return E;
}

template<typename T, int n>
const SquareMatrix<T, n> SquareMatrix<T, n>::transposition (int i, int j) {
    SquareMatrix<T, n> P = identity;
    P[i][i] = 0;
    P[j][j] = 0;
    P[i][j] = 1;
    P[j][i] = 1;
    return P;
}

/*! \relates SquareMatrix
  вычисление обратной матрицы
  \param M - матрица
  \return матрица, обратная к \a M (нулевая матрица в случае вырожденности \a M)
*/
template<typename T, int n>
const SquareMatrix<T, n> inverse (const SquareMatrix<T, n>& M) {
    SquareMatrix<T, n> inverse;
    if (M.det(inverse) == 0) {
        inverse = SquareMatrix<T, n>::null();
    }
    return inverse;
}

/*! \relates SquareMatrix
  вычисление определителя матрицы
  \param M - матрица
  \return определитель \a M
*/
template<typename T, int n>
T det (const SquareMatrix<T, n>& M) {
    SquareMatrix<T, n> inverse;
    return M.det(inverse);
}

/*! \relates SquareMatrix
  вычисление следа матрицы
  \param M - матрица
  \return след \a M
*/
template<typename T, int n>
T tr (const SquareMatrix<T, n>& M) {
    return algorithms::tr(M.array(), n);
}

}

#endif
