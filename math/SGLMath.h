#ifndef SGLMATH_H
#define SGLMATH_H

#include "vec4.h"
#include "mat4x4.h"

namespace SFL {

    // -- types ---------------------
    typedef sfl_vec3<int> ivec3;
    typedef sfl_vec4<int> ivec4;

    typedef sfl_vec3<float> vec3;
    typedef sfl_vec4<float> vec4;
    typedef sfl_mat3<float> mat3;
    typedef sfl_mat4<float> mat4;


    // -- value left multiply vector or matrix ---------------------
    template<typename T> sfl_vec3<T> operator + (const T &, const sfl_vec3<T> &);
    template<typename T> sfl_vec3<T> operator - (const T &, const sfl_vec3<T> &);
    template<typename T> sfl_vec3<T> operator * (const T &, const sfl_vec3<T> &);
    template<typename T> sfl_vec3<T> operator / (const T &, const sfl_vec3<T> &);

    template<typename T> sfl_vec4<T> operator + (const T &, const sfl_vec4<T> &);
    template<typename T> sfl_vec4<T> operator - (const T &, const sfl_vec4<T> &);
    template<typename T> sfl_vec4<T> operator * (const T &, const sfl_vec4<T> &);
    template<typename T> sfl_vec4<T> operator / (const T &, const sfl_vec4<T> &);

    template<typename T> sfl_mat3<T> operator + (const T &, const sfl_mat3<T> &);
    template<typename T> sfl_mat3<T> operator - (const T &, const sfl_mat3<T> &);
    template<typename T> sfl_mat3<T> operator * (const T &, const sfl_mat3<T> &);
    template<typename T> sfl_mat3<T> operator / (const T &, const sfl_mat3<T> &);

    template<typename T> sfl_mat4<T> operator + (const T &, const sfl_mat4<T> &);
    template<typename T> sfl_mat4<T> operator - (const T &, const sfl_mat4<T> &);
    template<typename T> sfl_mat4<T> operator * (const T &, const sfl_mat4<T> &);
    template<typename T> sfl_mat4<T> operator / (const T &, const sfl_mat4<T> &);


    // -- vector left multiply matrix ---------------------
    template<typename T> sfl_mat3<T> operator * (const sfl_vec3<T> &, const sfl_mat3<T> &);
    template<typename T> sfl_mat4<T> operator * (const sfl_vec4<T> &, const sfl_mat4<T> &);


    // -- test ---------------------
    template<typename T> void print(const sfl_vec3<T> &);
    template<typename T> void print(const sfl_vec4<T> &);

    template<typename T> void print(const sfl_mat3<T> &);
    template<typename T> void print(const sfl_mat4<T> &);


    // -- linear algebra ---------------------
    template<typename T> T distance(const sfl_vec3<T> &, const sfl_vec3<T> &);
    template<typename T> T distance(const sfl_vec4<T> &, const sfl_vec4<T> &);

    template<typename T> sfl_vec3<T> normalize(const sfl_vec3<T> &);
    template<typename T> sfl_vec4<T> normalize(const sfl_vec4<T> &);
}

#include "SGLMath.cpp"

#endif // SGLMATH_H
