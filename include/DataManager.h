#pragma once

#include <stdint.h>

#include <filesystem>
#include <string>

namespace filesystem = std::filesystem;
using std::string;

class DataManager {
 private:
  size_t data_сounter;
  filesystem::path file_path;

  filesystem::path createDirData(const string& file_path);

  /**
   * @brief Записывает данные меньше 20 байт в указанный фаил
   */
  size_t writeToFile(const uint8_t* p_data, size_t p_size,
                     const string& file_name);

 public:
  /**
   * @param file_path Строка с адресом хранения файлов с данными.
   */
  DataManager(const string& file_path = "../data");

  size_t set(const uint8_t* p_data, size_t p_size);
  size_t get(size_t p_offset, size_t p_size, const uint8_t* p_result);
};
