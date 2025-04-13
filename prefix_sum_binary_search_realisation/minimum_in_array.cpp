#include <iostream>
#include <vector>
int main() {
  int count_elems;
  std::cin >> count_elems;
  std::vector<long long> elems(count_elems);
  for (int i = 0; i < count_elems; ++i) {
    long long x;
    std::cin >> x;
    elems[i] = x;
  }
  std::vector<long long> min_left(count_elems + 1);
  std::vector<long long> min_right(count_elems + 1);
  min_left[0] = elems[0];
  min_right[0] = elems[count_elems - 1];
  for (int i = 0; i < count_elems; ++i) {
    min_left[i + 1] = std::min(min_left[i], elems[i]);
    min_right[i + 1] = std::min(min_right[i], elems[count_elems - 1 - i]);
  }
  int querys;
  std::cin >> querys;
  for (int i = 0; i < querys; ++i) {
    int left_gr;
    int right_gr;
    std::cin >> left_gr >> right_gr;
    std::cout << std::min(min_left[left_gr],
                          min_right[count_elems - right_gr + 1])
              << '\n';
  }
}
