/**
@file main.cpp
@brief Главный файл с точкой входа.
@cond
*/
#include <iostream>
#include <memory>
#include "geometry.h"
#include "parser.h"
#include "tgaimage.h"
/**
@endcond

@brief Рисует треугольник на изображении
@param t0,t1,t2 Вершины треугольника в пространстве экранных координат
@param image Изображение, на котором рисуется треугольник
@param color Цвет треугольника
*/
void triangle(vec3f t0, vec3f t1, vec3f t2, TGAImage& image, TGAColor color);
/**
@brief Создает матрицу вида
@param eye Позиция камеры
@param center Точка, на которую камера смотрит
@param up Вектор, задающий направление "вверх" для камеры
@return Матрица вида
*/
matrix lookat(vec3f eye, vec3f center, vec3f up);
/**
@brief Создает матрицу перспективного преобразования
@param x,y,w,h Определяют положение и размеры области вывода в пространстве
экранных координат
@return Матрица перспективного преобразования
*/
matrix viewport(int x, int y, int w, int h);

/// @brief Ширина изображения (в пикселях)
const int width = 800;
/// @brief Высота изображения (в пикселях)
const int height = 800;
/// @brief Глубина изображения (в пикселях)
const int depth = 255;

/// @brief Указатель на модель
std::unique_ptr<Model> model = NULL;
/// @brief Глобальный массив z-буфера
std::unique_ptr<int[]> zbuffer = NULL;

int main(int argc, char** argv) {
  // Проверка на наличие модели
  if (2 == argc) {
    model = std::make_unique<Model>(Model(argv[1]));
  } else {
    std::cout << "Give *.obj file, please";
    return 0;
  }
  vec3f eye;
  vec3f center;
  vec3f up;
  // Задание настроек
  {
    float a, b, c;
    std::cout << "Input camera coordinate (in format 'x y z'): ";
    std::cin >> a >> b >> c;
    eye = vec3f{b, c, a};
    std::cout << "Input center coordinate (in format 'x y z'): ";
    std::cin >> a >> b >> c;
    center = vec3f{b, c, a};
    std::cout << "Input camera up vector (in format 'x y z'): ";
    std::cin >> a >> b >> c;
    up = vec3f{b, c, a};
  }
  vec3f light_dir = eye.normalized();

  matrix ModelView = lookat(eye, center, up);
  matrix Projection = matrix();
  Projection[3][2] = -1.f / (eye - center).norm();
  matrix ViewPort =
      viewport(width / 8, height / 8, width * 3 / 4, height * 3 / 4);
  // Инициализация z-буфера
  zbuffer = std::make_unique<int[]>(width * height);
  for (int i = 0; i < width * height; i++) {
    zbuffer[i] = std::numeric_limits<int>::min();
  }
  // Рисование модели
  TGAImage image(width, height, TGAImage::RGB);
  for (int i = 0; i < model->nfaces(); i++) {
    std::vector<int> face = model->face(i);
    vec3f screen_coords[3];
    vec3f world_coords[3];
    for (int j = 0; j < 3; j++) {
      vec3f v = model->vert(face[j]);
      screen_coords[j] = ViewPort * (Projection * ModelView * (v));
      world_coords[j] = v;
    }
    vec3f n = (world_coords[2] - world_coords[0]) ^
              (world_coords[1] - world_coords[0]);
    n = n.normalized();
    float intensity = -(n * light_dir);
    if (intensity > 0) {
      triangle(
          screen_coords[0], screen_coords[1], screen_coords[2], image,
          TGAColor(intensity * 255, intensity * 255, intensity * 255, 255));
    } else {
      triangle(screen_coords[0], screen_coords[1], screen_coords[2], image,
               TGAColor(1, 1, 1, 255));
    }
  }

  image.flip_vertically();
  image.write_tga_file("output.tga");
  std::cout << "Finish!!";
  return 0;
}

matrix viewport(int x, int y, int w, int h) {
  matrix m = matrix();
  m[0][3] = x + w / 2.f;
  m[1][3] = y + h / 2.f;
  m[2][3] = depth / 2.f;

  m[0][0] = w / 2.f;
  m[1][1] = h / 2.f;
  m[2][2] = depth / 2.f;
  return m;
}

matrix lookat(vec3f eye, vec3f center, vec3f up) {
  vec3f z = (center - eye).normalized();
  vec3f x = (up ^ z).normalized();
  vec3f y = (z ^ x).normalized();
  matrix res = matrix();
  for (int i = 0; i < 3; i++) {
    res[0][i] = -x[i];
    res[1][i] = y[i];
    res[2][i] = -z[i];
    res[i][3] = -center[i];
  }
  return res;
}

void triangle(vec3f t0, vec3f t1, vec3f t2, TGAImage& image, TGAColor color) {
  if (t0.y == t1.y && t0.y == t2.y)
    return;
  if (t0.y > t1.y)
    std::swap(t0, t1);
  if (t0.y > t2.y)
    std::swap(t0, t2);
  if (t1.y > t2.y)
    std::swap(t1, t2);
  float total_height = t2.y - t0.y;
  for (int i = 0; i < total_height; i++) {
    bool second_half = i > t1.y - t0.y || t1.y == t0.y;
    float segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;
    float alpha = (float)i / total_height;
    float beta = (float)(i - (second_half ? t1.y - t0.y : 0)) / segment_height;
    vec3f A = t0 + (t2 - t0) * alpha;
    vec3f B = second_half ? t1 + (t2 - t1) * beta : t0 + (t1 - t0) * beta;
    if (A.x > B.x)
      std::swap(A, B);
    for (int j = A.x; j <= B.x; j++) {
      float phi = B.x == A.x ? 1. : (float)(j - A.x) / (float)(B.x - A.x);
      vec3f P = (A) + (B - A) * phi;
      int idx = int(P.x) + int(P.y) * width;
      if (P.x >= width || P.y >= height || P.x < 0 || P.y < 0)
        continue;
      if (zbuffer[idx] < P.z) {
        zbuffer[idx] = P.z;
        image.set(int(P.x + 0.5), int(P.y + 0.5), color);
      }
    }
  }
}