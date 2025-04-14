## Описание
### Содержание проекта
1. Класс DataManager для работы с бинарными данными в формате uint8_t*.
2. Консольный интерфейс для работы с классом в качестве примера.

### Описание DataManager
Данный класс создан для работы с данными, хронящимеся в виде массива, конкретно с uint8_t*.

Класс предоставляет возможность сохранять данные в файлы фиксированного размера. Данные сохраняются по порядку, в бинарные файлы с назвинями формата i.bin. i принимает значения от 1 до n. Данные добавленные ранее будет распологаться в файле с меньшим числом в названии. 

Все файлы заполняются полностью. Для примера: 
    
    Если было добавлено 50 байт данных, появятся 3 файла. Первый и второй фаил по 20 байт, трейтий 10 байт. 
    После добавления еще 30 байт, третий фаил будет заполнен до 20 байт, после чего будет создан еще один фаил 20 байт с оставшимеся данными.

С одной дерикторией можно работать неограниченное число сессий. При создании экземляра, в конструкторе считается число уже записанных данных в директории, что позволяет повторно подключится к папке с данными после окончания работы.

Выбор директории осуществляется при создании класса. В конструктор передается строка с путем. Если папки не сущесвтует, она будет создана. 

Класс может возвращать любой интервал данных записанных в дериктории. 

### Описание методов
- static DataManager* CreateDataManager(
      const string& file_path = "../../data/");
    - Описание: Фабричный метод 
    - Параметры: file_path строка с адресом дириктории под файлы данных
    - Возвращает: ссылку на объект или nullptr, если возникли проблемы при создании экземпляра.

- size_t Set(const uint8_t* p_data, size_t p_size);
    - Описание: Записывает данные в файлы
    - Параметры: p_data указатель на массив данных; p_size число элементов в массиве
    - Возвращает: число записанных байт

-  size_t Get(size_t p_offset, size_t p_size, vector<uint8_t>& p_result);
    - Описание: Записывает данные из файлов в вектор.
    - Параметры: p_offset указатель начала чтения; p_size число элементов для чтения
    - Возвращает: число прочитанных байт
   
Более точно описание элементов класа можно посмотреть в коде.

### CLI 
Файл main.cpp содержит простейшее консольное приложения в качестве примера для работы с классом DataManager.

## Запуск проекта

Проект собирается с помощью cmake версии 3.10 и выше. Для сборки:

1. Создайте папку для сборки. ```mkdir build```
2. Перейдите в неё. ```cd build  ```        
3. Сгенерируйте файлы сборки. ```cmake ..```
4. Запустите сборку. ```cmake --build .```
5. Запустите исполняемы фаил ```./DataManager``` на Linux или ```./Debug/DataManager.exe``` на Windows

Запуститься консольный интерфейс для работы с классом, в котором можно проверить работу.