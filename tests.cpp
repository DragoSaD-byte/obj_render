#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <cmath>
#include <iostream>
#include "doctest.h"
#include "geometry.h"
#include "parser.h"

TEST_CASE("Creation vec and operator[]") {
  vec<2> v2{0, 1};
  vec<3> v3 = {0, 1, 2};
  vec<4> v4 = {0, 1, 2, 3};
  for (int i = 0; i < 2; i++) {
    CHECK(v2[i] == float(i));
    CHECK_THROWS_AS(v2[i + 3], std::invalid_argument);
  }
  for (int i = 0; i < 3; i++) {
    CHECK(v3[i] == float(i));
    CHECK_THROWS_AS(v3[i + 4], std::invalid_argument);
  }
  for (int i = 0; i < 4; i++) {
    CHECK(v4[i] == float(i));
    CHECK_THROWS_AS(v4[i + 5], std::invalid_argument);
  }
}

TEST_CASE("operator+ adds two vectors of size n") {
  vec<3> v1 = {1, 2, 3};
  vec<3> v2 = {4, 5, 6};
  vec<3> result = v1 + v2;
  vec<3> expected = {5, 7, 9};
  CHECK(result[0] == expected[0]);
  CHECK(result[1] == expected[1]);
  CHECK(result[2] == expected[2]);
}

TEST_CASE("operator+ returns the same vector if added with zero vector") {
  vec<4> v1 = {1, 2, 3, 4};
  vec<4> v2 = {0, 0, 0, 0};
  vec<4> result = v1 + v2;
  CHECK(result[0] == v1[0]);
  CHECK(result[1] == v1[1]);
  CHECK(result[2] == v1[2]);
}

TEST_CASE(
    "operator+ adds negative vector to positive vector and returns the correct "
    "result") {
  for (int i = 0; i < 20; i++) {
    vec<2> v1 = {float(i), float(2 * i)};
    vec<2> v2 = {float(-i), float(-2 * i)};
    vec<2> result = v1 + v2;
    CHECK(result[0] == 0);
    CHECK(result[1] == 0);
    CHECK(result[2] == 0);
  }
}

TEST_CASE("operator- subtracts two vectors of size n") {
  vec<3> v1 = {1, 2, 3};
  vec<3> v2 = {4, 5, 6};
  vec<3> result = v1 - v2;
  vec<3> expected = {-3, -3, -3};
  CHECK(result[0] == expected[0]);
  CHECK(result[1] == expected[1]);
  CHECK(result[2] == expected[2]);
}

TEST_CASE("operator- returns the same vector if subtracted by zero vector") {
  vec<4> v1 = {1, 2, 3, 4};
  vec<4> v2 = {0, 0, 0, 0};
  vec<4> result = v1 - v2;
  CHECK(result[0] == v1[0]);
  CHECK(result[1] == v1[1]);
  CHECK(result[2] == v1[2]);
}

TEST_CASE("operator* multiplies two vectors of size n") {
  vec<3> v1 = {1, 2, 3};
  vec<3> v2 = {4, 5, 6};
  float result = v1 * v2;
  CHECK(result == 32);
}

TEST_CASE("operator* returns 0 if one of the vectors is zero vector") {
  vec<3> v1 = {1, 2, 3};
  vec<3> v2 = {0, 0, 0};
  float result = v1 * v2;
  CHECK(result == 0);
}

TEST_CASE("operator* multiplies a vector by a scalar") {
  vec<3> v1 = {2, 4, 6};
  double scalar = 0.5;
  vec<3> result = scalar * v1;
  vec<3> expected = {1, 2, 3};
  CHECK(result[0] == expected[0]);
  CHECK(result[1] == expected[1]);
  CHECK(result[2] == expected[2]);
}

TEST_CASE("operator* multiplies a vector by a scalar (reverse order)") {
  vec<3> v1 = {2, 4, 6};
  double scalar = 0.5;
  vec<3> result = v1 * scalar;
  vec<3> expected = {1, 2, 3};
  CHECK(result[0] == expected[0]);
  CHECK(result[1] == expected[1]);
  CHECK(result[2] == expected[2]);
}

TEST_CASE("operator/ throws an exception when divided by zero") {
  vec<2> v1 = {1, 2};
  float scalar = 0;
  CHECK_THROWS_AS(v1 / scalar, std::invalid_argument);
}

TEST_CASE("operator/ divides each element of the vector by a scalar") {
  vec<3> v1 = {6, 8, 10};
  float scalar = 2;
  vec<3> result = v1 / scalar;
  vec<3> expected = {3, 4, 5};
  CHECK(result[0] == expected[0]);
  CHECK(result[1] == expected[1]);
  CHECK(result[2] == expected[2]);
}

TEST_CASE("operator/ returns the same vector if divided by 1") {
  vec<4> v1 = {1, 2, 3, 4};
  float scalar = 1;
  vec<4> result = v1 / scalar;
  CHECK(result[0] == v1[0]);
  CHECK(result[1] == v1[1]);
  CHECK(result[2] == v1[2]);
}

TEST_CASE("Cross product of two vectors produces a vector orthogonal to both") {
  vec<3> v1{1, 0, 0};
  vec<3> v2{0, 1, 0};
  vec<3> expected{0, 0, 1};

  vec<3> result = v1 ^ v2;

  CHECK(result[0] == expected[0]);
  CHECK(result[1] == expected[1]);
  CHECK(result[2] == expected[2]);
}

TEST_CASE("Cross product can handle negative values") {
  vec<3> v1{1, 2, -3};
  vec<3> v2{-4, 5, 6};
  vec<3> expected{27, 6, 13};

  vec<3> result = v1 ^ v2;

  CHECK(result[0] == expected[0]);
  CHECK(result[1] == expected[1]);
  CHECK(result[2] == expected[2]);
}

TEST_CASE("Cross product of parallel vectors produces a zero vector") {
  vec<3> v1{1, 2, 3};
  vec<3> v2{2, 4, 6};
  vec<3> expected{0, 0, 0};

  vec<3> result = v1 ^ v2;

  CHECK(result[0] == expected[0]);
  CHECK(result[1] == expected[1]);
  CHECK(result[2] == expected[2]);
}

TEST_CASE("Matrix operations") {
  matrix m1;
  matrix m2;
  m2[0][0] = 2.0f;
  m2[1][1] = 3.0f;
  m2[2][2] = 4.0f;
  m2[3][3] = 5.0f;

  // Test operator[]
  m1[0][0] = 1.0f;
  CHECK(m1[0][0] == 1.0f);

  // Test operator* (matrix)
  matrix m3 = m1 * m2;
}

TEST_CASE("Model parser test") {
  Model model("test.obj");

  // Test constructor
  CHECK(model.nverts() == 4);
  CHECK(model.nfaces() == 2);

  // Test vert and face methods
  vec3f v1 = model.vert(0);
  CHECK(v1[0] == -1.0f);
  CHECK(v1[1] == -1.0f);
  CHECK(v1[2] == 1.0f);

  vec3f v2 = model.vert(1);
  CHECK(v2[0] == 1.0f);
  CHECK(v2[1] == -1.0f);
  CHECK(v2[2] == 1.0f);
}
