#include <iostream>
#include <vector>
int main() {
  int count_n = 0;
  int count_m = 0;
  int count_l = 0;
  int querys = 0;
  std::cin >> count_n >> count_m >> count_l;
  std::vector<std::vector<int>> a_arr(count_n, std::vector<int>(count_l));
  std::vector<std::vector<int>> b_arr(count_m, std::vector<int>(count_l));
  for (int i = 0; i < count_n; ++i) {
    for (int j = 0; j < count_l; ++j) {
      int x;
      std::cin >> x;
      a_arr[i][j] = x;
    }
  }
  for (int i = 0; i < count_m; ++i) {
    for (int j = 0; j < count_l; ++j) {
      int x;
      std::cin >> x;
      b_arr[i][j] = x;
    }
  }
  std::cin >> querys;
  for (int i = 0; i < querys; ++i) {
    int l;
    int r;
    int l_gr = 0;
    int r_gr = count_l - 1;
    int m = (l_gr + r_gr) / 2;
    std::cin >> l >> r;
    while (r_gr - l_gr > 1) {
      if (a_arr[l - 1][m] <= b_arr[r - 1][m]) {
        l_gr = m;
      } else {
        r_gr = m;
      }
      m = (r_gr + l_gr) / 2;
    }
    if (std::max(a_arr[l - 1][l_gr], b_arr[r - 1][l_gr]) <=
        std::max(a_arr[l - 1][r_gr], b_arr[r - 1][r_gr])) {
      std::cout << l_gr + 1;
    } else {
      std::cout << r_gr + 1;
    }
    std::cout << ' ';
  }
}
