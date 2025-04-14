#pragma once

#include <stdint.h>

#include <filesystem>
#include <string>
#include <vector>

namespace filesystem = std::filesystem;
using std::string;
using std::vector;

class DataManager {
 private:
  /**
   * @brief Содержит число записанных байт.
   */
  size_t data_counter_;
  /**
   * @brief Содержит размер файлов.
   */
  size_t file_space_;
  /**
   * @brief Дериктория для файлов.
   * @details В формате ../../{name}/
   */
  string file_path_;

  /**
   * @brief Создаёт дерикторию для файлов.
   */
  static string CreateDirData(const string& file_path);
  /**
   * @brief Записывает данные меньше 20 байт в указанный фаил.
   */
  size_t WriteToFile(const uint8_t* p_data, size_t p_size,
                     const string& file_name);
  /**
   * Вычисляет количесвто записанных байт в дерикторию объекта.
   */
  size_t CalcRecordBytes();
  /**
   * @brief Читает данные меньше 20 байт из указанного фаила.
   */
  vector<uint8_t> ReadFromFile(const string& filename, size_t p_offset,
                               size_t count);

  DataManager(const string& file_path);

 public:
  /**
   * @brief Фабричный метод для создания объектов класса.
   * @details Нужен для проверки корректности переданной дериктивы.
   */
  static DataManager* CreateDataManager(
      const string& file_path = "../../data/");
  /**
   * @brief Записывает данные из массива p_data в файлы.
   * @param p_data Указатель на массив данных.
   * @param p_size Число элементов в массиве.
   * @return Число записанных байт.
   */
  size_t Set(const uint8_t* p_data, size_t p_size);
  /**
   * @brief Читает данные из файлов в вектор.
   * @param p_offset Смещение начала интервала данных.
   * @param p_size Число элементов для чтения.
   * @return Вектор элементов.
   */
  size_t Get(size_t p_offset, size_t p_size, vector<uint8_t>& p_result);
  /**
   * @brief Возвращает число записанных в дерективу байтов.
   */
  size_t GetDataCounter();
};
