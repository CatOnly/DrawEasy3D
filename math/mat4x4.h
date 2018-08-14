#ifndef SFL_MAT4X4_H
#define SFL_MAT4X4_H

#include "vec4.h"
#include "mat3x3.h"

namespace SFL {

    template<typename T> class sfl_mat4
    {
        typedef sfl_vec4<T> SFLVec4;
        typedef sfl_mat4<T> SFLMat4;

        SFLVec4 _column[4];
        SFLVec4 row(int index) const {
            return SFLVec4(_column[0][index], _column[1][index], _column[2][index], _column[3][index]);
        }

    public:
        sfl_mat4(const SFLVec4 &col1, const SFLVec4 &col2, const SFLVec4 &col3, const SFLVec4 &col4){
            _column[0] = col1;
            _column[1] = col2;
            _column[2] = col3;
            _column[3] = col4;
        }
        sfl_mat4(const SFLMat4 &m4) {
            _column[0] = m4[0];
            _column[1] = m4[1];
            _column[2] = m4[2];
            _column[3] = m4[3];
        }
        sfl_mat4(const sfl_mat3<T> &m3){
            _column[0] = SFLVec4(m3[0]);
            _column[1] = SFLVec4(m3[1]);
            _column[2] = SFLVec4(m3[2]);
            _column[3] = SFLVec4(0.0, 0.0, 0.0, 1.0);
        }

        sfl_mat4(const T x1, const T x2, const T x3, const T x4,
                 const T y1, const T y2, const T y3, const T y4,
                 const T z1, const T z2, const T z3, const T z4,
                 const T w1, const T w2, const T w3, const T w4){
            _column[0] = SFLVec4(x1, x2, x3, x4);
            _column[1] = SFLVec4(y1, y2, y3, y4);
            _column[2] = SFLVec4(z1, z2, z3, z4);
            _column[3] = SFLVec4(w1, w2, w3, w4);
        }
        explicit sfl_mat4(const T value = 1.0f):sfl_mat4(
                                                    value, 0.0f, 0.0f, 0.0f,
                                                    0.0f, value, 0.0f, 0.0f,
                                                    0.0f, 0.0f, value, 0.0f,
                                                    0.0f, 0.0f, 0.0f,  1.0f
                                                ){}
        MAT_OPERATOR_INDEX(4)

        MAT_OPERATOR_BASE(4, +)
        MAT_OPERATOR_BASE(4, -)
        MAT_OPERATOR_BASE(4, /)

        MAT_OPERATOR(4, +=)
        MAT_OPERATOR(4, -=)
        MAT_OPERATOR(4, /=)

        MAT_OPERATOR_FLOAT_BASE(4, +)
        MAT_OPERATOR_FLOAT_BASE(4, -)
        MAT_OPERATOR_FLOAT_BASE(4, *)
        MAT_OPERATOR_FLOAT_BASE(4, /)

        MAT_OPERATOR_FLOAT(4, +=)
        MAT_OPERATOR_FLOAT(4, -=)
        MAT_OPERATOR_FLOAT(4, *=)
        MAT_OPERATOR_FLOAT(4, /=)

        SFLMat4 operator * (const SFLMat4 &m4) {
            SFLVec4 row0 = row(0);
            SFLVec4 row1 = row(1);
            SFLVec4 row2 = row(2);
            SFLVec4 row3 = row(3);

            SFLVec4 col0 = m4[0];
            SFLVec4 col1 = m4[1];
            SFLVec4 col2 = m4[2];
            SFLVec4 col3 = m4[3];

            return SFLMat4(
                row0.dot(col0), row1.dot(col0), row2.dot(col0), row3.dot(col0),
                row0.dot(col1), row1.dot(col1), row2.dot(col1), row3.dot(col1),
                row0.dot(col2), row1.dot(col2), row2.dot(col2), row3.dot(col2),
                row0.dot(col3), row1.dot(col3), row2.dot(col3), row3.dot(col3)
            );
        }

        SFLMat4& operator *= (const SFLMat4 &m4) {
            SFLVec4 row0 = row(0);
            SFLVec4 row1 = row(1);
            SFLVec4 row2 = row(2);
            SFLVec4 row3 = row(3);

            SFLVec4 col0 = m4[0];
            SFLVec4 col1 = m4[1];
            SFLVec4 col2 = m4[2];
            SFLVec4 col3 = m4[3];

            _column[0][0] = row0.dot(col0);
            _column[0][1] = row1.dot(col0);
            _column[0][2] = row2.dot(col0);
            _column[0][3] = row3.dot(col0);

            _column[1][0] = row0.dot(col1);
            _column[1][1] = row1.dot(col1);
            _column[1][2] = row2.dot(col1);
            _column[1][3] = row3.dot(col1);

            _column[2][0] = row0.dot(col2);
            _column[2][1] = row1.dot(col2);
            _column[2][2] = row2.dot(col2);
            _column[2][3] = row3.dot(col2);

            _column[3][0] = row0.dot(col3);
            _column[3][1] = row1.dot(col3);
            _column[3][2] = row2.dot(col3);
            _column[3][3] = row3.dot(col3);

            return *this;
        }

        SFLVec4 operator * (const SFLVec4 &col) {
            return SFLVec4(row(0).dot(col), row(1).dot(col), row(2).dot(col), row(3).dot(col));
        }

        const T *valuePtr() const {
            return &(_column[0][0]);
        }

        T det() const {
            return _column[0][0] * _column[1][1] * _column[2][2] * _column[3][3] - _column[0][0] * _column[1][3] * _column[2][2] * _column[3][1] +
                   _column[0][1] * _column[1][2] * _column[2][3] * _column[3][0] - _column[0][1] * _column[1][0] * _column[2][3] * _column[3][2] +
                   _column[0][2] * _column[1][3] * _column[2][0] * _column[3][1] - _column[0][2] * _column[1][1] * _column[2][0] * _column[3][3] +
                   _column[0][3] * _column[1][0] * _column[2][1] * _column[3][2] - _column[0][3] * _column[1][2] * _column[2][1] * _column[3][0];
        }
    };
}

#endif // SFL_MAT4X4_H
