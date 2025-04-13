#include <algorithm>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::max;
using std::min;
using std::sort;
using std::vector;
bool Comp(vector<int> left, vector<int> right) {
  return min(2 * left[0], 2 * left[1] + 1) <
         min(2 * right[0], 2 * right[1] + 1);
}
int main() {
  int n_count;
  cin >> n_count;
  vector<vector<int>> works(n_count, vector<int>(3));
  vector<vector<int>> first_elems;
  vector<vector<int>> second_elems;
  for (int i = 0; i < n_count; ++i) {
    int x_elem;
    cin >> x_elem;
    works[i][0] = x_elem;
  }
  for (int i = 0; i < n_count; ++i) {
    int x_elem;
    cin >> x_elem;
    works[i][1] = x_elem;
  }
  for (int i = 0; i < n_count; ++i) {
    works[i][2] = i + 1;
  }
  sort(works.begin(), works.end(), Comp);
  for (int i = 0; i < (int)works.size(); ++i) {
    if (works[i][0] <= works[i][1]) {
      first_elems.push_back(works[i]);
    } else {
      second_elems.push_back(works[i]);
    }
  }
  for (int j = second_elems.size() - 1; j != -1; --j) {
    first_elems.push_back(second_elems[j]);
  }
  long long a_1 = 0;
  long long a_2 = 0;
  for (int i = 0; i < n_count; ++i) {
    a_1 += first_elems[i][0];
    a_2 = max(a_2, a_1) + first_elems[i][1];
  }
  cout << a_2 << '\n';
  for (int i = 0; i < (int)first_elems.size(); ++i) {
    cout << first_elems[i][2] << ' ';
  }
  cout << '\n';
  for (int i = 0; i < (int)first_elems.size(); ++i) {
    cout << first_elems[i][2] << ' ';
  }
}

