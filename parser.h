/**
@file Parser.h
@brief Данный файл предоставляет интсрументарий для загрузки в память 3d модели
из .obj файла
@cond
*/
#include <vector>
#include "geometry.h"
/**
@endcond
@brief Класс, представляющий модель, загруженную из файла
*/
class Model {
 private:
  ///@brief Вектор вершин модели
  std::vector<vec3f> verts_;
  ///@brief Вектор граней модели
  std::vector<std::vector<int> > faces_;

 public:
  /**
  @brief Конструктор класса Model
  @param filename Имя файла, из которого будет загружена модель
  */
  Model(const char* filename);
  ~Model();      /// @brief Деструктор класса Mode
  int nverts();  /// @brief Возвращает количество вершин в модели
  int nfaces();  /// @brief Возвращает количество граней в модели
  /**
@brief Возвращает вершину модели с заданным индексом
@param i Индекс вершины
@return Вершина модели с заданным индексом в виде вектора (vec3f) координат
*/
  vec3f vert(int i);
  /**
  @brief Возвращает грань модели с заданным индексом
  @param idx Индекс грани
  @return Грань модели с заданным индексом в виде списка граней, входящих в неё
  */
  std::vector<int> face(int idx);
};