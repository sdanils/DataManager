#include "DataManager.h"

#include <filesystem>
#include <fstream>
#include <string>

namespace filesystem = std::filesystem;
using std::string;

filesystem::path dataDirCreate(const string& file_path) {
  filesystem::path target_dir = file_path;

  try {
    if (!filesystem::exists(target_dir)) {
      filesystem::create_directory(target_dir);
    }
    return target_dir;
  } catch (const filesystem::filesystem_error& e) {
    return "";
  }
};

DataManager::DataManager(const string& file_path_ = "../data") {
  file_path = dataDirCreate(file_path_);
  data_сounter = 0;
}

size_t DataManager::writeToFile(const uint8_t* p_data, size_t p_size,
                                const string& file_name) {
  std::ofstream file(file_name, std::ios::binary | std::ios::app);
  if (!file.is_open()) {
    return 0;
  }

  file.write(reinterpret_cast<const char*>(p_data), p_size);
  if (!file.good()) {
    return 0;
  }
  return p_size;
}

size_t DataManager::set(const uint8_t* p_data, size_t p_size) { return 0; }

size_t DataManager::get(size_t p_offset, size_t p_size,
                        const uint8_t* p_result) {
  return 0;
}
