#include <stdint.h>

#include <iostream>
#include <vector>

#include "data_manager.h"

using std::vector;

void AddData(const int data_bytes, DataManager* new_manager) {
  uint8_t* array = new uint8_t[data_bytes];

  for (int i = 0; i < data_bytes; i++) {
    array[i] = i % 255;
  }

  new_manager->Set(array, data_bytes);
  delete array;
}

string coutM(string masseg) {
  std::cout << masseg;
  string answer;
  std::cin >> answer;
  return answer;
}

int main() {
  string answer = coutM("Change the file directories (../data/)? Y/n: ");
  string file_dir = "../data/";
  if (answer.size() == 1 && answer[0] == 'Y') {
    file_dir = coutM("Enter new directory: ");
  }

  DataManager* new_manager = DataManager::CreateDataManager(file_dir);
  if (!new_manager) {
    std::cout << "Uncorrect entry.";
    return -1;
  }

  while (answer != "end") {
    std::cout << "\nBytes saved: "
              << std::to_string(new_manager->GetDataCounter()) << "\n";
    answer = coutM(
        "Enter 1 to save the data.\nEnter 2 to get the data.\nEnter other to "
        "exit: ");
    if (answer == "1") {
      int size_data = stoi(
          coutM("Enter number bytes (Array of data from 1 is automatically "
                "generated): "));
      AddData(size_data, new_manager);
    } else if (answer == "2") {
      int offset = stoi(coutM("Enter offset in data: "));
      unsigned long long int size_data = stoi(coutM("Enter number bytes: "));
      vector<uint8_t> result;
      size_data = new_manager->Get(offset, size_data, result);
      std::cout << "Result: ";
      for (int i = 0; i < size_data; i++) {
        std::cout << std::to_string(result[i]) << " ";
      }
    } else {
      answer = "end";
    }
    std::cout << "\n";
  }

  return 1;
}