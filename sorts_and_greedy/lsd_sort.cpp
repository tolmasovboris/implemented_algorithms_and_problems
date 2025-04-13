#include <cstdint>
#include <iostream>
#include <vector>
using std::vector;
const uint64_t cSys = 1 << 8;
const int cPart = 8;
void Lsdsort(std::vector<uint64_t>& arr) {
  std::vector<std::vector<uint64_t>> sortierung_array(cSys);
  uint64_t factor = 1;
  for (size_t i = 0; i < cPart; ++i) {
    for (size_t j = 0; j < arr.size(); ++j) {
      sortierung_array[(arr[j] / factor) % cSys].push_back(arr[j]);
    }
    arr.clear();
    for (size_t j = 0; j < cSys; ++j) {
      for (size_t k = 0; k < sortierung_array[j].size(); ++k) {
        arr.push_back(sortierung_array[j][k]);
      }
      sortierung_array[j].clear();
    }
    factor *= cSys;
  }
}
int main() {
  size_t n_count = 0;
  std::cin >> n_count;
  std::vector<uint64_t> numbers(n_count);
  for (size_t i = 0; i < n_count; ++i) {
    uint64_t x;
    std::cin >> x;
    numbers[i] = x;
  }
  Lsdsort(numbers);
  for (size_t i = 0; i < n_count; ++i) {
    std::cout << numbers[i] << ' ';
  }
}

