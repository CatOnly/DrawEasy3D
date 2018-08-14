#ifndef SFL_MAT3X3_H
#define SFL_MAT3X3_H

#include "vec3.h"

#define MAT_OPERATOR_INDEX(size) \
SFLVec##size& operator[](int i) {\
    assert(i >= 0 && i < size);\
    return _column[i];\
}\
SFLVec##size const& operator[](int i) const {\
    assert(i >= 0 && i < size);\
    return _column[i];\
}

#define MAT_OPERATOR_BASE(size, symbol)\
SFLMat##size operator symbol (const SFLMat##size &m){\
    SFLMat##size mTmp;\
    for (int i = 0; i < size; ++i){\
        mTmp[i] = _column[i] symbol m[i];\
    }\
\
    return mTmp;\
}
#define MAT_OPERATOR(size, symbol)\
SFLMat##size& operator symbol (const SFLMat##size &m){\
    for (int i = 0; i < size; ++i){\
        _column[i] symbol m[i];\
    }\
\
    return *this;\
}

#define MAT_OPERATOR_FLOAT_BASE(size, symbol)\
SFLMat##size operator symbol (const T value){\
    SFLMat##size mTmp;\
    for (int i = 0; i < size; ++i){\
        mTmp[i] = _column[i] symbol value;\
    }\
\
    return mTmp;\
}
#define MAT_OPERATOR_FLOAT(size, symbol)\
SFLMat##size& operator symbol (const T &value){\
    for (int i = 0; i < size; ++i){\
        _column[i] symbol value;\
    }\
\
    return *this;\
}

namespace SFL {

    template<typename T> class sfl_mat3
    {
        typedef sfl_vec3<T> SFLVec3;
        typedef sfl_mat3<T> SFLMat3;

        SFLVec3 _column[3];
        SFLVec3 row(int index) const {
            return SFLVec3(_column[0][index], _column[1][index], _column[2][index]);
        }

    public:
        sfl_mat3(const SFLVec3 &col1, const SFLVec3 &col2, const SFLVec3 &col3){
            _column[0] = col1;
            _column[1] = col2;
            _column[2] = col3;
        }

        sfl_mat3(const SFLMat3 &m3) {
            _column[0] = m3[0];
            _column[1] = m3[1];
            _column[2] = m3[2];
        }

        sfl_mat3(const T x1, const T x2, const T x3,
                 const T y1, const T y2, const T y3,
                 const T z1, const T z2, const T z3){
            _column[0] = SFLVec3(x1, x2, x3);
            _column[1] = SFLVec3(y1, y2, y3);
            _column[2] = SFLVec3(z1, z2, z3);
        }
        sfl_mat3(const T x, const T y, const T z):sfl_mat3(x, 0.0f, 0.0f,
                                                           0.0f, y, 0.0f,
                                                           0.0f, 0.0f, z){}
        explicit sfl_mat3(const T value = 1.0f):sfl_mat3(value, value, value){}

        MAT_OPERATOR_INDEX(3)

        MAT_OPERATOR_BASE(3, +)
        MAT_OPERATOR_BASE(3, -)
        MAT_OPERATOR_BASE(3, /)

        MAT_OPERATOR(3, +=)
        MAT_OPERATOR(3, -=)
        MAT_OPERATOR(3, /=)

        MAT_OPERATOR_FLOAT_BASE(3, +)
        MAT_OPERATOR_FLOAT_BASE(3, -)
        MAT_OPERATOR_FLOAT_BASE(3, *)
        MAT_OPERATOR_FLOAT_BASE(3, /)

        MAT_OPERATOR_FLOAT(3, +=)
        MAT_OPERATOR_FLOAT(3, -=)
        MAT_OPERATOR_FLOAT(3, *=)
        MAT_OPERATOR_FLOAT(3, /=)

        SFLMat3 operator * (const SFLMat3 &m3) {
            SFLVec3 row0 = row(0);
            SFLVec3 row1 = row(1);
            SFLVec3 row2 = row(2);

            SFLVec3 col0 = m3[0];
            SFLVec3 col1 = m3[1];
            SFLVec3 col2 = m3[2];

            return SFLMat3(
                row0.dot(col0), row1.dot(col0), row2.dot(col0),
                row0.dot(col1), row1.dot(col1), row2.dot(col1),
                row0.dot(col2), row1.dot(col2), row2.dot(col2)
            );
        }

        SFLMat3& operator *= (const SFLMat3 &m3) {
            SFLVec3 row0 = row(0);
            SFLVec3 row1 = row(1);
            SFLVec3 row2 = row(2);

            SFLVec3 col0 = m3[0];
            SFLVec3 col1 = m3[1];
            SFLVec3 col2 = m3[2];

            _column[0][0] = row0.dot(col0);
            _column[0][1] = row1.dot(col0);
            _column[0][2] = row2.dot(col0);

            _column[1][0] = row0.dot(col1);
            _column[1][1] = row1.dot(col1);
            _column[1][2] = row2.dot(col1);

            _column[2][0] = row0.dot(col2);
            _column[2][1] = row1.dot(col2);
            _column[2][2] = row2.dot(col2);

            return *this;
        }

        SFLVec3 operator * (const SFLVec3 &col) const {
            return SFLVec3(row(0).dot(col), row(1).dot(col), row(2).dot(col));
        }

        const T *valuePtr() const {
            return &(_column[0][0]);
        }

        T det() const {
            return _column[0][0] * _column[1][1] * _column[2][2] - _column[0][0] * _column[1][2] * _column[2][1] +
                   _column[0][1] * _column[1][2] * _column[2][0] - _column[0][1] * _column[1][0] * _column[2][2] +
                   _column[0][2] * _column[1][0] * _column[2][1] - _column[0][2] * _column[1][1] * _column[2][0];
        }
    };
}

#endif // SFL_MAT3X3_H
