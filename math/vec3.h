#ifndef VEC3_H
#define VEC3_H

#include "base.h"

#define V3_OPERATOR_LAST(symbol) \
vec3 operator symbol (int){\
    vec3 tmp(*this);\
    symbol x;\
    symbol y;\
    symbol z;\
\
    return tmp;\
}
#define V3_OPERATOR_FIRST(symbol) \
vec3& operator symbol (){\
    symbol x;\
    symbol y;\
    symbol z;\
\
    return *this;\
}

#define V3_OPERATOR_BASE(symbol) \
vec3 operator symbol (const vec3 &a){\
    return vec3(x symbol a.x, y symbol a.y, z symbol a.z);\
}
#define V3_OPERATOR(symbol) \
vec3& operator symbol (const vec3 &a){\
    x symbol a.x;\
    y symbol a.y;\
    z symbol a.z;\
\
    return *this;\
}

#define V3_OPERATOR_FLOAT_BASE(symbol) \
vec3 operator symbol (const float &a){\
    return vec3(x symbol a, y symbol a, z symbol a);\
}
#define V3_OPERATOR_FLOAT(symbol) \
vec3& operator symbol (const float &a){\
    x symbol a;\
    y symbol a;\
    z symbol a;\
\
    return *this;\
}

namespace SFL {
    class vec3
    {
    public:
        union { float x, r, s;};
        union { float y, g, t;};
        union { float z, b, p;};

        vec3(float x, float y, float z):x(x),y(y),z(z){}
        vec3(float x = 0.0f):vec3(x, x, x){}
        vec3(const vec3 &vec):vec3(vec.x, vec.y, vec.z){}

        VEC_OPERATOR_SQUARE(3)

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

        float dot(vec3 &right){
            return x * right.x + y * right.y + z * right.z;
        }
        vec3 cross(vec3 &right){
            return vec3(
                y * right.z - z * right.y,
                z * right.x - x * right.z,
                x * right.y - y * right.x
            );
        }
    };
}

#endif // VEC3_H
