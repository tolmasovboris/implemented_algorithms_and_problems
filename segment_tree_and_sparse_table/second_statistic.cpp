#include <cmath>
#include <iostream>
#include <set>
#include <vector>
using std::cin;
using std::cout;
using std::min;
using std::pair;
using std::vector;
int MinElement(int l_gr, int r_gr,
               vector<vector<pair<long long, int>>>& sparse) {
  int diff = r_gr - l_gr + 1;
  int power = __builtin_clzll(1) - __builtin_clzll(diff);
  pair<long long, int> ind =
      min(sparse[power][l_gr], sparse[power][r_gr - (1 << power) + 1]);
  int min_elem = ind.second;
  return min_elem;
}

int main() {
  size_t n_count = 0;
  size_t q_count = 0;
  cin >> n_count >> q_count;
  vector<pair<long long, int>> values(n_count, {0, 0});
  for (size_t i = 0; i < n_count; ++i) {
    long long x_elem;
    cin >> x_elem;
    values[i] = {x_elem, i};
  }
  size_t maxpow = ceil(std::log2(n_count));
  vector<vector<pair<long long, int>>> sparse(
      maxpow + 1, vector<pair<long long, int>>(n_count, {0, 0}));
  sparse[0] = values;
  for (size_t k = 1; k <= maxpow; k++) {
    for (size_t ind = 0; ind + (1 << k) <= n_count; ind++) {
      sparse[k][ind] =
          min(sparse[k - 1][ind], sparse[k - 1][ind + (1 << (k - 1))]);
    }
  }
  for (size_t i = 0; i < q_count; ++i) {
    long long ans = 0;
    int l_gr = 0;
    int r_gr = 0;
    cin >> l_gr >> r_gr;
    int min_ind = MinElement(l_gr - 1, r_gr - 1, sparse);

    if (min_ind == l_gr - 1) {
      ans = values[MinElement(l_gr, r_gr - 1, sparse)].first;

    } else if (min_ind == r_gr - 1) {
      ans = values[MinElement(l_gr - 1, r_gr - 2, sparse)].first;

    } else {
      ans = min(values[MinElement(l_gr - 1, min_ind - 1, sparse)].first,
                values[MinElement(min_ind + 1, r_gr - 1, sparse)].first);
    }
    cout << ans << '\n';
  }
}
