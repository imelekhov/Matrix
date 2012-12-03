#ifndef _MATRIX_SCALARMATRIX_H
#define _MATRIX_SCALARMATRIX_H

#include <GenericMatrix.h>
#include <identity_t.h>

namespace Matrix {

/*! \class ScalarMatrix
  \brief Шаблон ScalarMatrix - класс реализации общих математических операций с матрицами-скалярами
  \tparam T - тип единственного элемента матрицы
*/
template<typename T>
class ScalarMatrix : public GenericMatrix<T, 1, 1> {
private:
    void operator [] (int); // объявление запрещает использование оператора [] для ScalarMatrix
protected:
    using GenericMatrix<T, 1, 1>::m_array;
public:
/*!
  конструктор по умолчанию
*/
    ScalarMatrix (void) : GenericMatrix<T, 1, 1>() {
    }

/*!
  конструктор копирования
  \param other - копируемая матрица
*/
    ScalarMatrix (const ScalarMatrix& other) : GenericMatrix<T, 1, 1>(other) {
    }

/*!
  конструктор копирования
  \param other - копируемая матрица
*/
    ScalarMatrix (const GenericMatrix<T, 1, 1>& other) : GenericMatrix<T, 1, 1>(other) {
    }

/*!
  конструктор из литерала нулевой матрицы
*/
    ScalarMatrix (null_t) : GenericMatrix<T, 1, 1>() {
        m_array[0][0] = 0;
    }

/*!
  конструктор из литерала единичной матрицы
*/
    ScalarMatrix (identity_t) : GenericMatrix<T, 1, 1>() {
        m_array[0][0] = 1;
    }

/*!
  конструктор из скаляра
  \param s - скаляр инициализации
*/
    ScalarMatrix (const T& s) : GenericMatrix<T, 1, 1>() {
        m_array[0][0] = s;
    }

/*!
  оператор присваивания скаляру единичного значения
*/
    ScalarMatrix& operator = (identity_t) {
        m_array[0][0] = 1;
        return *this;
    }

/*!
  оператор копирования скаляра
  \param s - копируемый скаляр
*/
    ScalarMatrix& operator = (const T& s) {
        m_array[0][0] = s;
        return *this;
    }

/*!
  оператор приведения к скалярному типу
  \return единственный элемент матрицы
*/
    operator T (void) const {
        return m_array[0][0];
    }
};

}

#endif
