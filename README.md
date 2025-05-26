# Курсовой проект "3D-Renderer"

# Сборка

Если сборка происходит под Windows, то рекомендуется использовать x64 тулчейн (например, используя x64 Native tools Command Prompt), так как при сборке под x86 срабатывает assert внутри библиотеки Eigen.

```
cmake -DCMAKE_BUILD_TYPE=Release -S src/ -B build/
cmake --build build/
```

Собранная программа будет находиться по пути `./<build dir>/application/Debug/application.exe`

Запуск:
```
application <путь-до-модели>
```
