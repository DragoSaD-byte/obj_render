#include "geometry.h"

vec3f operator*(const matrix& a, const vec3f& b) {
  vec<4> t{b.x, b.y, b.z, 1};
  vec<4> result;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      result[i] += a[i][j] * t[j];
    }
  }
  return vec3f{result[0] / result[3], result[1] / result[3],
               result[2] / result[3]};
}

matrix operator*(const matrix& a, const matrix& b) {
  matrix result;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      result[i][j] = 0.f;
      for (int k = 0; k < 4; k++) {
        result[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return result;
}

vec<3> operator^(const vec<3>& lhs, const vec<3>& rhs) {
  return vec<3>{lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z,
                lhs.x * rhs.y - lhs.y * rhs.x};
}