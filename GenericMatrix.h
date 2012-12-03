#ifndef _MATRIX_GENERICMATRIX_H
#define _MATRIX_GENERICMATRIX_H

#include <null_t.h>
#include "algorithms.h"

namespace Matrix {

/*! \class GenericMatrix
  \brief Шаблон GenericMatrix - класс реализации общих математических операций с матрицами
  \tparam T - тип элементов матрицы
  \tparam n - количество строк матрицы
  \tparam m - количество столбцов матрицы
*/
template<typename T, int n, int m>
class GenericMatrix {
public:
/*! \typedef ElementType
  тип элементов матрицы
*/
    typedef T ElementType;

/*!
  количество строк матрицы
*/
    static const int rows = n;

/*!
  количество столбцов матрицы
*/
    static const int columns = m;
private:
/*! \class RowConst
  \brief Класс RowConst - константный указатель на строку матрицы
*/
    class RowConst {
        const T* m_row;
        RowConst (const T* row) : m_row(row) {
        }
        RowConst (const RowConst& other);
        RowConst& operator = (const RowConst& other);
    public:
        const T& operator [] (int column) const {
            return m_row[column];
        }
    friend const RowConst GenericMatrix::operator [] (int) const;
    };

/*! \class Row
  \brief Класс Row - указатель на строку матрицы
*/
    class Row {
        T* m_row;
        Row (T* row) : m_row(row) {
        }
        Row (const Row& other);
        Row& operator = (const Row& other);
    public:
        T& operator [] (int column) const {
            return m_row[column];
        }
    friend const Row GenericMatrix::operator [] (int);
    };
protected:
/*!
  двумерный массив элементов матрицы
*/
    T m_array[n][m];
public:
/*!
  конструктор по умолчанию
*/
    GenericMatrix (void) {
    }

/*!
  конструктор копирования
  \param other - копируемая матрица
*/
    GenericMatrix (const GenericMatrix& other) {
        algorithms::cp(array(), other.array(), n, m);
    }

/*!
  конструктор из литерала нулевой матрицы
*/
    GenericMatrix (null_t) {
        algorithms::null(array(), n, m);
    }

/*!
  конструктор из списка инициализации
  \param list - список инициализации
*/
    GenericMatrix (const std::initializer_list<std::initializer_list<T>>& list) {
        algorithms::cp(array(), list, n, m);
    }


/*!
  оператор копирования
  \param other - копируемая матрица
*/
    GenericMatrix& operator = (const GenericMatrix& other) {
        algorithms::cp(array(), other.array(), n, m);
        return *this;
    }

/*!
  оператор обнуления матрицы
*/
    GenericMatrix& operator = (null_t) {
        algorithms::null(array(), n, m);
        return *this;
    }

/*!
  оператор умножения на скаляр
  \param scalar - скалярный множитель
  \return матрица, умноженная на \a scalar
*/
    GenericMatrix& operator *= (const T& scalar) {
        algorithms::mul(array(), scalar, n, m);
        return *this;
    }

/*!
  оператор прибавления другой матрицы
  \param other - другая матрица
  \return матрица, увеличенная на \a other
*/
    GenericMatrix& operator += (const GenericMatrix& other) {
        algorithms::add(array(), other.array(), n, m);
        return *this;
    }

/*!
  оператор вычитания другой матрицы
  \param other - другая матрица
  \return матрица, уменьшенная на \a other
*/
    GenericMatrix& operator -= (const GenericMatrix& other) {
        algorithms::sub(array(), other.array(), n, m);
        return *this;
    }

/*!
  оператор индексации
  \param row - индекс строки матрицы
  \return объект \a RowConst - константный указатель на строку в двумерном массиве элементов матрицы
*/
    const RowConst operator [] (int row) const {
        return RowConst(m_array[row]);
    }

/*!
  оператор индексации
  \param row - индекс строки матрицы
  \return объект \a Row - указатель на строку в двумерном массиве элементов матрицы
*/
    const Row operator [] (int row) {
        return Row(m_array[row]);
    }

/*!
  массив элементов матрицы
  \return константный указатель на начало массива элементов матрицы
*/
    const T* array (void) const {
        return (const T*) m_array;
    }

/*!
  массив элементов матрицы
  \return указатель на начало массива элементов матрицы
*/
    T* array (void) {
        return (T*) m_array;
    }
};

/*! \relates GenericMatrix
  оператор равенства
  \param lhs - левая сторона равенства
  \param rhs - правая сторона равенства
  \return \a true, если матрицы \a lhs и \a rhs совпадают поэлементно
*/
template<typename T, int n, int m>
bool operator == (const GenericMatrix<T, n, m>& lhs, const GenericMatrix<T, n, m>& rhs) {
    return algorithms::cmp(lhs.array(), rhs.array(), n, m);
}

/*! \relates GenericMatrix
  оператор неравенства
  \param lhs - левая сторона неравенства
  \param rhs - правая сторона неравенства
  \return \a true, если матрицы \a lhs и \a rhs отличаются хотя бы в одном элементе
*/
template<typename T, int n, int m>
bool operator != (const GenericMatrix<T, n, m>& lhs, const GenericMatrix<T, n, m>& rhs) {
    return !algorithms::cmp(lhs.array(), rhs.array(), n, m);
}

/*! \relates GenericMatrix
  оператор сложения
  \param lhs - первое слагаемое
  \param rhs - второе слагаемое
  \return сумма матриц \a lhs и \a rhs
*/
template<typename T, int n, int m>
const GenericMatrix<T, n, m> operator + (const GenericMatrix<T, n, m>& lhs, const GenericMatrix<T, n, m>& rhs) {
    GenericMatrix<T, n, m> M = lhs;
    return M += rhs;
}

/*! \relates GenericMatrix
  оператор унарного минуса
  \param rhs - матрица
  \return матрица, противоположная к \a rhs
*/
template<typename T, int n, int m>
const GenericMatrix<T, n, m> operator - (const GenericMatrix<T, n, m>& rhs) {
    GenericMatrix<T, n, m> M = null;
    return M -= rhs;
}

/*! \relates GenericMatrix
  оператор вычитания
  \param lhs - уменьшаемая матрица
  \param rhs - вычитаемая матрица
  \return разность матриц \a lhs и \a rhs
*/
template<typename T, int n, int m>
const GenericMatrix<T, n, m> operator - (const GenericMatrix<T, n, m>& lhs, const GenericMatrix<T, n, m>& rhs) {
    GenericMatrix<T, n, m> M = lhs;
    return M -= rhs;
}

/*! \relates GenericMatrix
  оператор умножения матрицы и скаляра
  \param lhs - матричный множитель
  \param rhs - скалярный множитель
  \return произведение матрицы \a lhs и скаляра \a rhs
*/
template<typename T, int n, int m>
const GenericMatrix<T, n, m> operator * (const GenericMatrix<T, n, m>& lhs, const T& rhs) {
    GenericMatrix<T, n, m> M = lhs;
    return M *= rhs;
}

/*! \relates GenericMatrix
  оператор умножения скаляра и матрицы
  \param lhs - скалярный множитель
  \param rhs - матричный множитель
  \return произведение скаляра \a lhs и матрицы \a rhs
*/
template<typename T, int n, int m>
const GenericMatrix<T, n, m> operator * (const T& lhs, const GenericMatrix<T, n, m>& rhs) {
    GenericMatrix<T, n, m> M = rhs;
    return M *= lhs;
}

/*! \relates GenericMatrix
  оператор умножения матриц
  \tparam n - количество строк первого множителя
  \tparam k - количество столбцов первого множителя, равное количеству строк второго множителя
  \tparam m - количество столбцов второго множителя
  \param lhs - первый множитель, матрица \a n x \a k
  \param rhs - второй множитель, матрица \a k x \a m
  \return произведение матриц \a lhs и \a rhs, матрица \a n x \a m
*/
template<typename T, int n, int k, int m>
const GenericMatrix<T, n, m> operator * (const GenericMatrix<T, n, k>& lhs, const GenericMatrix<T, k, m>& rhs) {
    GenericMatrix<T, n, m> M;
    algorithms::mul(M.array(), lhs.array(), rhs.array(), n, k, m);
    return M;
}

/*! \relates GenericMatrix
  конкатенация матриц
  \tparam n - количество строк в конкатенируемых матрицах
  \tparam m1 - количество столбцов в первой матрице
  \tparam m2 - количество столбцов в второй матрице
  \param lhs - матрица \a n x \a m1
  \param rhs - матрица \a n x \a m2
  \return матрица \a n x (\a m1 + \a m2), полученная конкатенацией (по горизонтали) матриц \a lhs и \a rhs
*/
template<typename T, int n, int m1, int m2>
const GenericMatrix<T, n, m1 + m2> cat (const GenericMatrix<T, n, m1>& lhs, const GenericMatrix<T, n, m2>& rhs) {
    GenericMatrix<T, n, m1 + m2> M;
    algorithms::cat(M.array(), lhs.array(), rhs.array(), n, m1, m2);
    return M;
}

/*! \relates GenericMatrix
  минор матрицы
  \tparam n1 - количество строк минора
  \tparam m1 - количество столбцов минора
  \param M - матрица
  \param i0 - верхняя строка минора
  \param j0 - левый столбец минора
  \return минор матрицы \a M, матрица \a n1 x \a m1
*/
template<typename T, int n, int m, int n1, int m1>
const GenericMatrix<T, n1, m1> minor (const GenericMatrix<T, n, m>& M, int i0, int j0) {
    GenericMatrix<T, n1, m1> R;
    algorithms::minor(R.array(), M.array(), i0, j0, n, m, n1, m1);
    return R;
}

/*! \relates GenericMatrix
  главный минор матрицы
  \tparam n1 - количество строк минора
  \tparam m1 - количество столбцов минора
  \param M - матрица
  \return главный минор матрицы \a M, матрица \a n1 x \a m1
*/
template<typename T, int n, int m, int n1, int m1>
inline const GenericMatrix<T, n1, m1> minor (const GenericMatrix<T, n, m>& M) {
    return minor<T, n, m, n1, m1>(M, 0, 0);
}

/*! \relates GenericMatrix
  дополнение матрицы нулями до матрицы большего размера
  \tparam n1 - количество строк, до которого дополняется матрица
  \tparam m1 - количество столбцов, до которого дополняется матрица
  \param M - матрица
  \param i0 - индекс верхней строки матрицы в дополненной матрице
  \param j0 - индекс левого стролбца матрицы в дополненной матрице
  \return матрица \a n1 x \a m1, содержащая матрицу \a M в качестве минора
*/
template<typename T, int n, int m, int n1, int m1>
const GenericMatrix<T, n1, m1> expand (const GenericMatrix<T, n, m>& M, int i0, int j0) {
    GenericMatrix<T, n1, m1> R;
    algorithms::expand(R.array(), M.array(), i0, j0, n, m, n1, m1);
    return R;
}

/*! \relates GenericMatrix
  дополнение матрицы нулями до матрицы большего размера
  \tparam n1 - количество строк, до которого дополняется матрица
  \tparam m1 - количество столбцов, до которого дополняется матрица
  \param M - матрица
  \return матрица \a n1 x \a m1, содержащая матрицу \a M в качестве главного минора
*/
template<typename T, int n, int m, int n1, int m1>
inline const GenericMatrix<T, n1, m1> expand (const GenericMatrix<T, n, m>& M) {
    return expand<T, n, m, n1, m1>(M, 0, 0);
}

/*! \relates GenericMatrix
  "норма" матрицы
  \param M - матрица
  \return сумма квадратов элементов матрицы \a M
*/
template<typename T, int n, int m>
T norm (const GenericMatrix<T, n, m>& M) {
    return algorithms::norm(M.array(), n, m);
}

/*! \relates GenericMatrix
  запись матрицы в поток вывода в бинарном виде
  \tparam Stream - тип потока вывода
  \param stream - поток вывода
  \param M - матрица
  \return поток вывода
*/
template<typename T, int n, int m, typename Stream>
Stream& operator << (Stream& stream, const GenericMatrix<T, n, m>& M) {
//  return algorithms::pack(stream, M.array(), n, m);
    return algorithms::print(stream, M.array(), n, m);
}

/*! \relates GenericMatrix
  чтение матрицы из потока ввода в бинарном виде
  \tparam Stream - тип потока ввода
  \param stream - поток ввода
  \param M - матрица
  \return поток ввода
*/
template<typename T, int n, int m, typename Stream>
Stream& operator >> (Stream& stream, GenericMatrix<T, n, m>& M) {
    return algorithms::unpack(stream, M.array(), n, m);
}

}

#endif
