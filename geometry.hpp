#pragma once
#include <cmath>

struct vec {
    double data[2] = {0};
    inline double& operator[](const int i)       { return data[i]; }
    inline double  operator[](const int i) const { return data[i]; }
    double norm2() const { return *this * *this; }
    double norm()  const { return std::sqrt(norm2()); }
	inline double& x() {return data[0];}
	inline double& y() {return data[1];}
	friend double operator*(const vec& lhs, const vec& rhs) {
		double ret = 0;
		for (int i=2; i--; ret+=lhs[i]*rhs[i]);
			return ret;
	}
};

vec operator+(const vec& lhs, const vec& rhs) {
    vec ret = lhs;
    for (int i=2; i--; ret[i]+=rhs[i]);
    return ret;
}

vec operator-(const vec& lhs, const vec& rhs) {
    vec ret = lhs;
    for (int i=2; i--; ret[i]-=rhs[i]);
    return ret;
}

vec operator*(const double& rhs, const vec &lhs) {
    vec ret = lhs;
    for (int i=2; i--; ret[i]*=rhs);
    return ret;
}

vec operator*(const vec& lhs, const double& rhs) {
    vec ret = lhs;
    for (int i=2; i--; ret[i]*=rhs);
    return ret;
}

vec operator/(const vec& lhs, const double& rhs) {
    vec ret = lhs;
    for (int i=2; i--; ret[i]/=rhs);
    return ret;
}