#ifndef VEC4_H
#define VEC4_H
#include "base.h"

#define V4_OPERATOR_LAST(symbol) \
vec4 operator symbol (int){\
    vec4 tmp(*this);\
    symbol x;\
    symbol y;\
    symbol z;\
    symbol w;\
\
    return tmp;\
}
#define V4_OPERATOR_FIRST(symbol) \
vec4& operator symbol (){\
    symbol x;\
    symbol y;\
    symbol z;\
    symbol w;\
\
    return *this;\
}

#define V4_OPERATOR_BASE(symbol) \
vec4 operator symbol (const vec4 &a){\
    return vec4(x symbol a.x, y symbol a.y, z symbol a.z, w symbol a.w);\
}
#define V4_OPERATOR(symbol) \
vec4& operator symbol (const vec4 &a){\
    x symbol a.x;\
    y symbol a.y;\
    z symbol a.z;\
    w symbol a.w;\
\
    return *this;\
}

namespace SFL {
    class vec4
    {
    public:
        union { float x, r, s; };
        union { float y, g, t; };
        union { float z, b, p; };
        union { float w, a, q; };

        vec4(float x, float y, float z, float w):x(x),y(y),z(z),w(w){}
        vec4(float x = 0.0f):vec4(x,x,x,x){}
        vec4(const vec4 &vec):vec4(vec.x, vec.y, vec.z, vec.w){}

        VEC_OPERATOR_SQUARE(4)

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

        float dot(vec4 &a){
            return x * a.x + y * a.y + z * a.z + w * a.w;
        }
    };
}

#endif // VEC4_H
