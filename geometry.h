#pragma once
#include <cmath>
#include <iostream>

template<class type, int n>
struct vec {
    type data[n] = {0};
    type& operator[](const int i)       { return data[i]; }
    type  operator[](const int i) const { return data[i]; }
    type norm2() const { return *this * *this; }
    double norm()  const { return std::sqrt(norm2()); }
};

template<class type, int n>
type operator*(const vec<type,n>& lhs, const vec<type,n>& rhs) {
    type ret = 0;
    for (int i=n; i--; ret+=lhs[i]*rhs[i]);
    return ret;
}

template<class type, int n>
vec<type,n> operator+(const vec<type,n>& lhs, const vec<type,n>& rhs) {
    vec<type,n> ret = lhs;
    for (int i=n; i--; ret[i]+=rhs[i]);
    return ret;
}

template<class type, int n>
vec<type,n> operator-(const vec<type,n>& lhs, const vec<type,n>& rhs) {
    vec<type,n> ret = lhs;
    for (int i=n; i--; ret[i]-=rhs[i]);
    return ret;
}

template<class type, int n>
vec<type,n> operator*(const double& rhs, const vec<type,n> &lhs) {
    vec<type,n> ret = lhs;
    for (int i=n; i--; ret[i]*=rhs);
    return ret;
}

template<class type, int n>
vec<type,n> operator*(const vec<type,n>& lhs, const double& rhs) {
    vec<type,n> ret = lhs;
    for (int i=n; i--; ret[i]*=rhs);
    return ret;
}

template<class type, int n>
vec<type,n> operator/(const vec<type,n>& lhs, const double& rhs) {
    vec<type,n> ret = lhs;
    for (int i=n; i--; ret[i]/=rhs);
    return ret;
}



template<class type>
struct vec<type, 2> {
    type x = 0, y = 0;
    type& operator[](const int i)       { return i ? y : x; }
    type  operator[](const int i) const { return i ? y : x; }
    type norm2() const { return *this * *this; }
    double norm()  const { return std::sqrt(norm2()); }
    vec<type, 2> normalized() { return (*this)/norm(); }
};

template<class type>
struct vec<type, 3> {
    type x = 0, y = 0, z = 0;
    type& operator[](const int i)       { return i ? (1==i ? y : z) : x; }
    type  operator[](const int i) const { return i ? (1==i ? y : z) : x; }
    type norm2() const { return *this * *this; }
    double norm()  const { return std::sqrt(norm2()); }
    vec<type, 3> normalized() { return (*this)/norm(); }
};

template<class type>
vec<type, 3> operator^(const vec<type,3>& lhs, const vec<type,3>& rhs) {
    return vec<type, 3>{lhs.y*rhs.z-lhs.z*rhs.y, lhs.z*rhs.x-lhs.x*rhs.z, lhs.x*rhs.y-lhs.y*rhs.x};
}

typedef vec<int, 2> vec2i;
typedef vec<int, 3> vec3i;
typedef vec<float, 2> vec2f;
typedef vec<float, 3> vec3f;


struct matrix {
    float data[4][4];
	matrix() {
		for (int i=0; i<4; i++) {
			for (int j=0; j<4; j++) {
				data[i][j] = (i==j ? 1.f : 0.f);
			}
		}
	};
	float* operator[](const int i)       { return data[i]; }
    const float *  operator[](const int i) const { return data[i]; }
};


matrix operator*(const matrix& a, const matrix& b);

vec<float, 3> operator*(const matrix& a, const vec<float, 3>& b);
