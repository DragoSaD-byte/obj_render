# obj_render
Программа является простым 3d рендером для учебных целей.

## Компиляция
```sh
git clone https://github.com/DragoSaD-byte/obj_render.git
cd obj_render
mkdir build
cd build
cmake ..
cmake --build .
```
## Использование
Для запуска тестов необходим файл test.obj в одном каталоге с файлом Test.exe, который появиться после компиляции. Как только это условие будет соблюдено, можно запустить файл и провести тесты.

Для запуска самого рендера необходимо указать .obj файл, который вы хотите отрендерить. 
Далее программа попросит ввести координаты камеры, центра и вектор "верха" камеры (который будет направден вверх на самом изображении).
Если всё пройдёт успешно программа выведет "Finish!!" и сохранит изображение в файл output.tga.
```sh
Render.exe demon.obj
Input camera coordinate (in format 'x y z'): 1 0 0
Input center coordinate (in format 'x y z'): 0 0 0
Input camera up vector (in format 'x y z'): 0 0 1
```
Пример вывода для данного варианта:
![output](https://github.com/DragoSaD-byte/obj_render/assets/115976948/4cee6c2e-852a-48c1-8ed8-efcf012a795d)

```sh
Render.exe demon.obj
Input camera coordinate (in format 'x y z'): 1 0 0
Input center coordinate (in format 'x y z'): 0 0 0
Input camera up vector (in format 'x y z'): 0 1 0
```
Пример вывода для данного варианта:
![output](https://github.com/DragoSaD-byte/obj_render/assets/115976948/b37c3004-bccf-480f-9573-1658125d7ddd)
