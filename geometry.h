/**
@file geometry.h
@brief Определение некоторых структур (вектор длинны n и матрица 4 на 4),
необходимых для более удобной работы с геометрией.
@cond
*/

#pragma once
#include <cmath>
#include <iostream>

/**
@endcond
@brief Шаблон структуры vec, представляющий вектор размерности n.
@tparam n Размерность вектора.
*/
template <int n>
struct vec {
  /**
  @brief Элементы вектора.
  */
  float data[n] = {0};
  /**
  @brief Оператор доступа к элементу вектора по ссылке.
  @param i Индекс элемента.
  @return Ссылка на элемент вектора с заданным индексом.
  @throw std::invalid_argument Если индекс выходит за пределы размерности
  вектора.
  */
  float& operator[](const int i) {
    if (i >= n) {
      throw std::invalid_argument(
          "The length of the vector is less than the inversion index");
    }
    return data[i];
  }
  /**
  @brief Оператор доступа к элементу вектора по значению.
  @param i Индекс элемента.
  @return Значение элемента вектора с заданным индексом.
  @throw std::invalid_argument Если индекс выходит за пределы размерности
  вектора.
  */
  float operator[](const int i) const {
    if (i >= n) {
      throw std::invalid_argument(
          "The length of the vector is less than the inversion index");
    }
    return data[i];
  }
  /**
  @brief Вычисляет квадрат нормы вектора.
  @return Квадрат нормы вектора.
  */
  float norm2() const { return *this * *this; }
  /**
  @brief Вычисляет норму вектора.
  @return Норма вектора.
  */
  double norm() const { return std::sqrt(norm2()); }
};

/**

@brief Оператор скалярного произведения двух векторов.
@tparam n Размерность векторов.
@param lhs Левый вектор.
@param rhs Правый вектор.
@return Скалярное произведение векторов.
*/
template <int n>
float operator*(const vec<n>& lhs, const vec<n>& rhs) {
  float ret = 0;
  for (int i = n; i--; ret += lhs[i] * rhs[i])
    ;
  return ret;
}
/**

@brief Оператор сложения двух векторов.
@tparam n Размерность векторов.
@param lhs Левый вектор.
@param rhs Правый вектор.
@return Результат сложения векторов.
*/
template <int n>
vec<n> operator+(const vec<n>& lhs, const vec<n>& rhs) {
  vec<n> ret = lhs;
  for (int i = n; i--; ret[i] += rhs[i])
    ;
  return ret;
}
/**

@brief Оператор вычитания двух векторов.
@tparam n Размерность векторов.
@param lhs Левый вектор.
@param rhs Правый вектор.
@return Результат вычитания векторов.
*/
template <int n>
vec<n> operator-(const vec<n>& lhs, const vec<n>& rhs) {
  vec<n> ret = lhs;
  for (int i = n; i--; ret[i] -= rhs[i])
    ;
  return ret;
}
/**

@brief Оператор умножения вектора на скаляр слева.
@tparam n Размерность вектора.
@param lhs Скалярное значение.
@param rhs Вектор.
@return Результат умножения вектора на скаляр справа.
*/
template <int n>
vec<n> operator*(const double& lhs, const vec<n>& rhs) {
  vec<n> ret = rhs;
  for (int i = n; i--; ret[i] *= lhs)
    ;
  return ret;
}
/**

@brief Оператор умножения вектора на скаляр справа.
@tparam n Размерность вектора.
@param lhs Вектор.
@param rhs Скалярное значение.
@return Результат умножения вектора на скаляр слева.
*/
template <int n>
vec<n> operator*(const vec<n>& lhs, const double& rhs) {
  vec<n> ret = lhs;
  for (int i = n; i--; ret[i] *= rhs)
    ;
  return ret;
}
/**

@brief Оператор деления вектора на скаляр.
@tparam n Размерность вектора.
@param lhs Вектор.
@param rhs Скалярное значение.
@return Результат деления вектора на скаляр.
@throw std::invalid_argument Если делитель равен нулю.
*/
template <int n>
vec<n> operator/(const vec<n>& lhs, const double& rhs) {
  if (rhs == 0) {
    throw std::invalid_argument("Division of a vector by zero");
  }
  vec<n> ret = lhs;
  for (int i = n; i--; ret[i] /= rhs)
    ;
  return ret;
}

template <>
struct vec<2> {
  float x = 0, y = 0;
  float& operator[](const int i) {
    if (i > 2) {
      throw std::invalid_argument(
          "The length of the vector is less than the inversion index");
    }
    return i ? y : x;
  }
  float operator[](const int i) const {
    if (i > 2) {
      throw std::invalid_argument(
          "The length of the vector is less than the inversion index");
    }
    return i ? y : x;
  }
  float norm2() const { return *this * *this; }
  double norm() const { return std::sqrt(norm2()); }
  vec<2> normalized() { return (*this) / norm(); }
};

template <>
struct vec<3> {
  float x = 0, y = 0, z = 0;
  float& operator[](const int i) {
    if (i > 2) {
      throw std::invalid_argument(
          "The length of the vector is less than the inversion index");
    }
    return i ? (1 == i ? y : z) : x;
  }
  float operator[](const int i) const {
    if (i > 2) {
      throw std::invalid_argument(
          "The length of the vector is less than the inversion index");
    }
    return i ? (1 == i ? y : z) : x;
  }
  float norm2() const { return *this * *this; }
  double norm() const { return std::sqrt(norm2()); }
  vec<3> normalized() { return (*this) / norm(); }
};

typedef vec<2> vec2f;
typedef vec<3> vec3f;

/**

@brief Структура matrix, представляющая 4x4 матрицу.
*/
struct matrix {
  /**
  @brief Элементы матрицы.
  */
  float data[4][4];
  /**
  @brief Конструктор, инициализирующий матрицу единичной матрицей.
  */
  matrix() {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        data[i][j] = (i == j ? 1.f : 0.f);
      }
    }
  };
  /**
  @brief Оператор доступа к строке матрицы по ссылке.
  @param i Индекс строки матрицы.
  @return Ссылка на строку матрицы с заданным индексом.
  */
  float* operator[](const int i) { return data[i]; }
  /**
  @brief Оператор доступа к строке матрицы по значению.
  @param i Индекс строки матрицы.
  @return Значение строки матрицы с заданным индексом.
  */
  const float* operator[](const int i) const { return data[i]; }
};
/**

@brief Оператор умножения двух матриц.
@param a Левая матрица.
@param b Правая матрица.
@return Результат умножения двух матриц.
*/
matrix operator*(const matrix& a, const matrix& b);
/**

@brief Оператор умножения матрицы на вектор.
@param a Матрица.
@param b Вектор.
@return Результат умножения матрицы на вектор.
*/
vec3f operator*(const matrix& a, const vec3f& b);
/**

@brief Оператор векторного произведения двух векторов типа vec3f.
@param lhs Левый вектор.
@param rhs Правый вектор.
@return Векторное произведение двух векторов типа vec3f.
*/
vec3f operator^(const vec3f& lhs, const vec3f& rhs);
