#include <cmath>
#include <iostream>
#include <vector>
int main() {
  const int cInf = 20;
  int n_elem;
  std::cin >> n_elem;
  std::vector<long double> elems(n_elem + 1);
  elems[0] = 1;
  for (int i = 0; i < n_elem; ++i) {
    float x;
    std::cin >> x;
    elems[i + 1] = elems[i] * pow(x, 1. / n_elem);
  }
  int q_elem;
  std::cin >> q_elem;
  for (int i = 0; i < q_elem; ++i) {
    long double ans = 0;
    int l;
    int r;
    std::cin >> l >> r;
    ans = elems[r + 1] / elems[l];
    std::cout << std::fixed;
    std::cout.precision(cInf);
    std::cout << std::pow(ans, n_elem / ((r - l + 1) * 1.0)) << '\n';
  }
}
