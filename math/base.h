#ifndef SFL_BASE_H
#define SFL_BASE_H

#include <cstddef>
#include <cassert>

#define VEC_OPERATOR_SQUARE(size) \
float & operator[](int i) {\
    assert(i >= 0 && i < size);\
    return (&x)[i];\
}\
float const& operator[](int i) const {\
    assert(i >= 0 && i < size);\
    return (&x)[i];\
}

#define MAT_OPERATOR_SQUARE(size) \
vec##size& operator[](int i){\
    assert(i >= 0 && i < size);\
    return column[i];\
}\
vec##size const&  operator[](int i) const{\
    assert(i >= 0 && i < size);\
    return column[i];\
}

#define MAT_OPERATOR_BASE(size, symbol)\
mat##size operator symbol (const mat##size &m){\
    mat##size mTmp;\
    for (int i = 0; i < size; ++i){\
        mTmp.column[i] = column[i] symbol m.column[i];\
    }\
\
    return mTmp;\
}

namespace SFL {

}

#endif // SFL_BASE_H
