#include <algorithm>
#include <iostream>
#include <vector>
bool CheckAccept(std::vector<long long> field, long long k_elem,
                 long long haves) {
  long long current_position = field[0] - 1;
  for (size_t i = 0; i < field.size(); ++i) {
    if (field[i] > current_position) {
      haves--;
      current_position = field[i] + k_elem;
    }
  }
  return haves >= 0;
}
int main() {
  const int cInf = 20;
  long long elems_n;
  long long count_k;
  std::cin >> elems_n >> count_k;
  std::vector<long long> elems(elems_n);
  for (int i = 0; i < elems_n; ++i) {
    long long x;
    std::cin >> x;
    elems[i] = x;
  }
  std::sort(elems.begin(), elems.end());
  long long left = -1;
  long long right = std::abs(elems[elems.size() - 1] - elems[0]) * cInf;
  while (right - left > 1) {
    long long mid = (left + right) / 2;
    if (CheckAccept(elems, mid, count_k)) {
      right = mid;
    } else {
      left = mid;
    }
  }
  std::cout << right;
}
