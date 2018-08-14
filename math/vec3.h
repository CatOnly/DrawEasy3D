#ifndef SFL_VEC3_H
#define SFL_VEC3_H

#include <cstddef>
#include <cassert>
#include <math.h>

#define VEC_OPERATOR_INDEX(size) \
float & operator[](int i) {\
    assert(i >= 0 && i < size);\
    return (&x)[i];\
}\
float const& operator[](int i) const {\
    assert(i >= 0 && i < size);\
    return (&x)[i];\
}

#define V3_OPERATOR_LAST(symbol) \
SFLVec3 operator symbol (int){\
    SFLVec3 tmp(*this);\
    symbol x;\
    symbol y;\
    symbol z;\
\
    return tmp;\
}
#define V3_OPERATOR_FIRST(symbol) \
SFLVec3& operator symbol (){\
    symbol x;\
    symbol y;\
    symbol z;\
\
    return *this;\
}

#define V3_OPERATOR_BASE(symbol) \
SFLVec3 operator symbol (const SFLVec3 &a){\
    return sfl_vec3(x symbol a.x, y symbol a.y, z symbol a.z);\
}
#define V3_OPERATOR(symbol) \
SFLVec3& operator symbol (const SFLVec3 &a){\
    x symbol a.x;\
    y symbol a.y;\
    z symbol a.z;\
\
    return *this;\
}

namespace SFL {

    template <typename T> class sfl_vec3
    {
    public:
        union { T x, r, s;};
        union { T y, g, t;};
        union { T z, b, p;};

        typedef sfl_vec3<T> SFLVec3;

        sfl_vec3(T x, T y, T z):x(static_cast<T>(x)),y(static_cast<T>(y)),z(static_cast<T>(z)){}
        sfl_vec3(T x = 0.0f):sfl_vec3(static_cast<T>(x), static_cast<T>(x), static_cast<T>(x)){}
        sfl_vec3(const SFLVec3 &vec):sfl_vec3(vec.x, vec.y, vec.z){}

        VEC_OPERATOR_INDEX(3)

        V3_OPERATOR_LAST(++)
        V3_OPERATOR_LAST(--)
        V3_OPERATOR_FIRST(++)
        V3_OPERATOR_FIRST(--)

        V3_OPERATOR_BASE(+)
        V3_OPERATOR_BASE(-)
        V3_OPERATOR_BASE(*)
        V3_OPERATOR_BASE(/)

        V3_OPERATOR(+=)
        V3_OPERATOR(-=)
        V3_OPERATOR(*=)
        V3_OPERATOR(/=)

        T dot(const SFLVec3 &vector) const {
            return x * vector.x + y * vector.y + z * vector.z;
        }

        SFLVec3 cross(const SFLVec3 &vector) const {
            return SFLVec3(
                y * vector.z - z * vector.y,
                z * vector.x - x * vector.z,
                x * vector.y - y * vector.x
            );
        }

        T length() const {
            return static_cast<T>(sqrt(x*x + y*y + z*z));
        }
    };
}

#endif // SFL_VEC3_H
