#include "data_manager.h"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace filesystem = std::filesystem;
using std::string;
using std::vector;

string DataManager::CreateDirData(const string& file_path) {
  filesystem::path target_dir = file_path;

  try {
    if (!filesystem::exists(target_dir)) {
      filesystem::create_directory(target_dir);
    }
    return target_dir.string();
  } catch (const filesystem::filesystem_error& e) {
    return "";
  }
};

size_t DataManager::CalcRecordBytes() {
  size_t total_bytes = 0;

  for (const auto& entry : filesystem::directory_iterator(file_path_)) {
    if (entry.is_regular_file()) {
      string filename = entry.path().filename().string();
      total_bytes += filesystem::file_size(entry);
    }
  }

  return total_bytes;
};

DataManager::DataManager(const size_t& file_space = 20,
                         const string& file_path = "../data") {
  file_path_ = CreateDirData(file_path);
  file_space_ = file_space;
  data_counter_ = CalcRecordBytes();
};

size_t DataManager::WriteToFile(const uint8_t* p_data, size_t p_size,
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
};

size_t DataManager::Set(const uint8_t* p_data, size_t p_size) {
  size_t written_bytes = 0;

  while (written_bytes < p_size) {
    size_t space_file = file_space_ - (data_counter_ % file_space_);
    int num_file = data_counter_ / file_space_ + 1;
    string file_name = std::to_string(num_file) + ".bin";
    size_t num_bytes = std::min(p_size - written_bytes, space_file);

    size_t result_write =
        WriteToFile(&p_data[written_bytes], num_bytes, file_name);
    written_bytes += result_write;
    data_counter_ += result_write;
  }

  return written_bytes;
};

vector<uint8_t> DataManager::ReadFromFile(const string& filename,
                                          size_t p_offset, size_t count) {
  std::ifstream file(filename, std::ios::binary);
  if (!file.is_open()) {
    return {};
  }
  file.seekg(p_offset, std::ios::beg);

  vector<uint8_t> data(count);
  file.read(reinterpret_cast<char*>(data.data()), count);

  if (!file.good()) {
    return {};
  }

  return data;
}

std::vector<uint8_t>& DataManager::Get(size_t p_offset, size_t p_size,
                                       const uint8_t* p_result) {
  if (p_offset >= data_counter_ || p_offset + p_size > data_counter_) {
    return {};
  }

  size_t read_bytes_num = 0;
  vector<uint8_t> result;

  while (read_bytes_num < p_size) {
    size_t current_offset = p_offset + read_bytes_num;
    int num_file = current_offset / file_space_ + 1;
    string file_name = std::to_string(num_file) + ".bin";
    size_t num_bytes = std::min(p_size - read_bytes_num,
                                file_space_ - current_offset % file_space_);

    vector<uint8_t> read_bytes =
        ReadFromFile(file_name, current_offset % 20, num_bytes);

    result.insert(result.end(), read_bytes.begin(), read_bytes.end());
    read_bytes_num += read_bytes.size();
  }

  return result;
};
