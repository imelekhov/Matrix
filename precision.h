#ifndef _MATRIX_PRECISION_H
#define _MATRIX_PRECISION_H

namespace Matrix {

/*!
  точность вычислений с числовым типом
  \tparam T - числовой тип
  \return малое неотрицательное число, превышение которого необходимо, чтобы число считалось ненулевым при вычислениях
*/
template<typename T>
inline T precision (void);

template<>
inline int precision (void) {
    return 0;
}

template<>
inline float precision (void) {
    return 1E-6;
}

template<>
inline double precision (void) {
    return 1E-12;
}

template<>
inline long double precision (void) {
    return 1E-15;
}

}

#endif
