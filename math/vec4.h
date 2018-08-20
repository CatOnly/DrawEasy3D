#ifndef SFL_VEC4_H
#define SFL_VEC4_H
#include "vec3.h"

#define V4_OPERATOR_LAST(symbol) \
SFLVec4 operator symbol (int){\
    SFLVec4 tmp(*this);\
    symbol x;\
    symbol y;\
    symbol z;\
    symbol w;\
\
    return tmp;\
}
#define V4_OPERATOR_FIRST(symbol) \
SFLVec4& operator symbol (){\
    symbol x;\
    symbol y;\
    symbol z;\
    symbol w;\
\
    return *this;\
}

#define V4_OPERATOR_BASE(symbol) \
SFLVec4 operator symbol (const SFLVec4 &a){\
    return SFLVec4(x symbol a.x, y symbol a.y, z symbol a.z, w symbol a.w);\
}
#define V4_OPERATOR(symbol) \
SFLVec4& operator symbol (const SFLVec4 &a){\
    x symbol a.x;\
    y symbol a.y;\
    z symbol a.z;\
    w symbol a.w;\
\
    return *this;\
}

namespace SFL {

    template <typename T> class sfl_vec4
    {
    public:
        union { T x, r, s; };
        union { T y, g, t; };
        union { T z, b, p; };
        union { T w, a, q; };

        typedef sfl_vec4<T> SFLVec4;

        sfl_vec4(T x, T y, T z, T w):x(static_cast<T>(x)),y(static_cast<T>(y)),z(static_cast<T>(z)),w(static_cast<T>(w)){}
        sfl_vec4(T x = 0.0f):sfl_vec4(static_cast<T>(x),static_cast<T>(x),static_cast<T>(x),static_cast<T>(x)){}
        sfl_vec4(const SFLVec4 &vec):sfl_vec4(vec.x, vec.y, vec.z, vec.w){}
        sfl_vec4(const sfl_vec3<T> &vec):sfl_vec4(vec.x, vec.y, vec.z, 0.0f){}

        VEC_OPERATOR_INDEX(4)

        V4_OPERATOR_LAST(++)
        V4_OPERATOR_LAST(--)
        V4_OPERATOR_FIRST(++)
        V4_OPERATOR_FIRST(--)

        V4_OPERATOR_BASE(+)
        V4_OPERATOR_BASE(-)
        V4_OPERATOR_BASE(*)
        V4_OPERATOR_BASE(/)

        V4_OPERATOR(+=)
        V4_OPERATOR(-=)
        V4_OPERATOR(*=)
        V4_OPERATOR(/=)

        T dot(const SFLVec4 &a) const {
            return x * a.x + y * a.y + z * a.z + w * a.w;
        }

        T length() const {
            return static_cast<T>(sqrt(x*x +  y*y + z*z));
        }
    };
}

#endif // SFL_VEC4_H
