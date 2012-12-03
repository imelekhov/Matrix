#ifndef _MATRIX_ALGORITHMS_H
#define _MATRIX_ALGORITHMS_H

#define USE_STD_EXCEPTIONS 1

#if USE_STD_EXCEPTIONS
#include <stdexcept>
#endif

#include <initializer_list>
#include <cmath>

/*! \def minor
  В некоторых системах Linux определен макрос minor
*/

#ifdef minor
#undef minor
#endif

#include "precision.h"

namespace Matrix {

namespace algorithms {

template<typename T>
void add (T* lhs, const T* rhs, int n, int m) {
    T* _lhs = lhs;
    const T* _rhs = rhs;
    int cnt = n * m;
    while (cnt--) {
        *_lhs++ += *_rhs++;
    }
}

template<typename T>
void cat (T* dst, const T* lhs, const T* rhs, int n, int m1, int m2) {
    T* _dst = dst;
    const T* _lhs = lhs;
    const T* _rhs = rhs;
    int i = n;
    while (i--) {
        int j = m1;
        while (j--) {
            *_dst++ = *_lhs++;
        }
        j = m2;
        while (j--) {
            *_dst++ = *_rhs++;
        }
    }
}

template<typename T>
bool cmp (const T* lhs, const T* rhs, int n, int m) {
    const T* _lhs = lhs;
    const T* _rhs = rhs;
    int cnt = n * m;
    while (cnt--) {
        if (*_lhs++ != *_rhs++) {
            return false;
        }
    }
    return true;
}

template<typename T>
void cp (T* dst, const T* src, int n, int m) {
    T* _dst = dst;
    const T* _src = src;
    int cnt = n * m;
    while (cnt--) {
        *_dst++ = *_src++;
    }
}

template<typename T>
void cp (T* dst, const std::initializer_list<std::initializer_list<T>>& list, int n, int m) {
#if USE_STD_EXCEPTIONS
    if ((int) list.size() != n) {
        throw std::runtime_error("wrong matrix initializer size");
    }
#endif
    T* _dst = dst;
    for (auto row: list) {
#if USE_STD_EXCEPTIONS
        if ((int) row.size() != m) {
            throw std::runtime_error("wrong matrix initializer size");
        }
#endif
        for (auto cell: row) {
            *_dst++ = cell;
        }
    }
}

template<typename T>
void cp (T* dst, const T* src, int n) {
    T* _dst = dst;
    const T* _src = src;
    int i = n;
    while (i--) {
        *_dst++ = *_src++;
    }
}

template<typename T>
void cp (T* dst, const std::initializer_list<T>& list, int n) {
#if USE_STD_EXCEPTIONS
    if ((int) list.size() != n) {
        throw std::runtime_error("wrong matrix initializer size");
    }
#endif
    T* _dst = dst;
    for (auto cell: list) {
        *_dst++ = cell;
    }
}

template<typename T>
T dot (const T* lhs, const T* rhs, int n) {
    const T* _lhs = lhs;
    const T* _rhs = rhs;
    T S = 0;
    int i = n;
    while (i--) {
        S += *_lhs++ * *_rhs++;
    }
    return S;
}

template<typename T>
T gauss (T* array, int n) {
    int i, j;
    T D = 1;
    for (j = 0; j < n; ++j) {
        for (i = j; i < n; ++i) {
            const T* cell = array + (2 * i + 1) * n + j;
            if (fabs(*cell) > precision<T>()) {
                if (i != j) {
                    T* cell_i = array + 2 * i * n;
                    T* cell_j = array + 2 * j * n;
                    int k = 2 * n;
                    while (k--) {
                        T swap = *cell_i;
                        *cell_i++ = *cell_j;
                        *cell_j++ = swap;
                    }
                    D = -D;
                }
                break;
            }
        }
        if (i == n) {
            return 0;
        }
        for (i = j + 1; i < n; ++i) {
            T* cell_i = array + (2 * i + 1) * n + j;
            T* cell_j = array + (2 * j + 1) * n + j;
            T mul = *cell_i / *cell_j;
            cell_i = array + 2 * i * n;
            cell_j = array + 2 * j * n;
            int k = 2 * n;
            while (k--) {
                *cell_i++ -= mul * *cell_j++;
            }
        }
    }
    for (j = 1; j < n; ++j) {
        for (i = j - 1; i >= 0; --i) {
            T* cell_i = array + (2 * i + 1) * n + j;
            T* cell_j = array + (2 * j + 1) * n + j;
            T mul = *cell_i / *cell_j;
            cell_i = array + 2 * i * n;
            cell_j = array + 2 * j * n;
            int k = 2 * n;
            while (k--) {
                *cell_i++ -= mul * *cell_j++;
            }
        }
    }
    for (i = 0; i < n; ++i) {
        T* cell = array + (2 * i + 1) * n + i;
        T mul = *cell;
        cell = array + 2 * i * n;
        int k = 2 * n;
        while (k--) {
            *cell++ /= mul;
        }
        D *= mul;
    }
    return D;
}

template<typename T>
void diag (T* dst, const T* src, int n) {
    T* _dst = dst;
    const T* _src = src;
    *_dst++ = *_src++;
    int i = n - 1;
    while (i--) {
        int j = n;
        while (j--) {
            *_dst++ = 0;
        }
        *_dst++ = *_src++;
    }
}

template<typename T>
void expand (T* dst, const T* src, int i0, int j0, int n, int m, int n1, int m1) {
    T* _dst = dst;
    const T* _src = src;
    int i = i0;
    while (i--) {
        int j = m1;
        while (j--) {
            *_dst++ = 0;
        }
    }
    i = n;
    while (i--) {
        int j = j0;
        while (j--) {
            *_dst++ = 0;
        }
        j = m;
        while (j--) {
            *_dst++ = *_src++;
        }
        j = m1 - m - j0;
        while (j--) {
            *_dst++ = 0;
        }
    }
    i = n1 - n - i0;
    while (i--) {
        int j = m1;
        while (j--) {
            *_dst++ = 0;
        }
    }
}

template<typename T>
void identity (T* dst, int n) {
    T* _dst = dst;
    *_dst++ = 1;
    int i = n - 1;
    while (i--) {
        int j = n;
        while (j--) {
            *_dst++ = 0;
        }
        *_dst++ = 1;
    }
}

template<typename T>
void minor (T* dst, const T* src, int i0, int j0, int, int m, int n1, int m1) {
    T* _dst = dst;
    const T* _src = src;
    _src += i0 * m;
    int i = n1;
    while (i--) {
        _src += j0;
        int j = m1;
        while (j--) {
            *_dst++ = *_src++;
        }
        _src += m - m1 - j0;
    }
}

template<typename T>
void mul (T* array, T scalar, int n, int m) {
    T* _array = array;
    int cnt = n * m;
    while (cnt--) {
        *_array++ *= scalar;
    }
}

template<typename T>
void mul (T* dst, const T* lhs, const T* rhs, int n, int k, int m) {
    T* _dst = dst;
    const T* lrow = lhs;
    int i = n;
    while (i--) {
        const T* rcolumn = rhs;
        int j = m;
        while (j--) {
            const T* lcell = lrow;
            const T* rcell = rcolumn;
            T S = 0;
            int l = k;
            while (l--) {
                S += *lcell * *rcell;
                ++lcell;
                rcell += m;
            }
            *_dst++ = S;
            ++rcolumn;
        }
        lrow += k;
    }
}

template<typename T>
T norm (const T* array, int n, int m) {
    const T* _array = array;
    T S = 0;
    int cnt = n * m;
    while (cnt--) {
        T item = *_array++;
        S += item * item;
    }
    return S;
}

template<typename T>
void null (T* dst, int n, int m) {
    T* _dst = dst;
    int cnt = n * m;
    while (cnt--) {
        *_dst++ = 0;
    }
}

template<typename T, typename Stream>
Stream& pack (Stream& stream, const T* array, int n, int m) {
    stream << n;
    stream << m;
    const T* _array = array;
    int cnt = n * m;
    while (cnt--) {
        stream << *_array++;
    }
    return stream;
}

#define LINEBREAK 0

template<typename T, typename Stream>
Stream& print (Stream& stream, const T* array, int n, int m) {
    const T* _array = array;
    stream << "{";
    int i = n;
    while (i--) {
        stream << "{";
        int j = m;
        while (j--) {
            stream << *_array++;
            if (j) {
                stream << ", ";
            }
        }
        stream << "}";
#if LINEBREAK
        stream << "\n";
#endif
        if (i) {
            stream << ", ";
        }
    }
    stream << "}";
#if LINEBREAK
    stream << "\n";
#endif
    return stream;
}

template<typename T, typename Stream>
Stream& print (Stream& stream, const T* array, int n) {
    const T* _array = array;
    stream << "{";
    int i = n;
    while (i--) {
        stream << *_array++;
        if (i) {
            stream << ", ";
        }
    }
    stream << "}";
#if LINEBREAK
    stream << "\n";
#endif
    return stream;
}

template<typename T>
void sub (T* lhs, const T* rhs, int n, int m) {
    T* _lhs = lhs;
    const T* _rhs = rhs;
    int cnt = n * m;
    while (cnt--) {
        *_lhs++ -= *_rhs++;
    }
}

template<typename T>
T tr (const T* array, int n) {
    const T* _array = array;
    T tr = *_array;
    int i = n - 1;
    while (i--) {
        _array += n + 1;
        tr += *_array;
    }
    return tr;
}

template<typename T>
void transpose (T* dst, const T* src, int n, int m) {
    T* _dst = dst;
    const T* column = src;
    int j = m;
    while (j--) {
        const T* cell = column;
        int i = n;
        while (i--) {
            *_dst++ = *cell;
            cell += m;
        }
        ++column;
    }
}

template<typename T, typename Stream>
Stream& unpack (Stream& stream, T* array, int n, int m) {
    int _n, _m;
    stream >> _n >> _m;
#if USE_STD_EXCEPTIONS
    if ((_n != n) || (_m != m)) {
        throw std::runtime_error("matrix size corrupted");
    }
#endif
    T* _array = array;
    int cnt = n * m;
    while (cnt--) {
        stream >> *_array++;
    }
    return stream;
}

}

}

#endif
