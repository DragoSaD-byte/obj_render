#include "geometry.h"

vec<float, 3> operator*(const matrix& a, const vec<float, 3>& b) {
    vec<float, 4> t{b.x,b.y,b.z,1};
	vec<float, 4> result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i] += a[i][j] * t[j];
        }
    }
    return vec<float, 3>{result[0]/result[3], result[1]/result[3], result[2]/result[3]};
}

matrix operator*(const matrix& a, const matrix& b) {
    matrix result;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            result[i][j] = 0.f;
            for (int k=0; k<4; k++) {
                result[i][j] += a[i][k]*b[k][j];
            }
        }
    }
    return result;
}