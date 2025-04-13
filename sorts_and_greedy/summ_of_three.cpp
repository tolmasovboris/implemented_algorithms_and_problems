#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using std::cin;
using std::cout;
using std::pair;
using std::vector;
int main() {
  int n_count;
  long long s_count = 0;
  cin >> s_count;
  vector<pair<long long, int>> a_arr;
  vector<pair<long long, int>> b_arr;
  vector<pair<long long, int>> c_arr;
  cin >> n_count;
  for (int i = 0; i < n_count; ++i) {
    int x_elem;
    cin >> x_elem;
    a_arr.push_back({x_elem, i});
  }
  cin >> n_count;
  for (int i = 0; i < n_count; ++i) {
    int x_elem;
    cin >> x_elem;
    b_arr.push_back({x_elem, i});
  }
  cin >> n_count;
  for (int i = 0; i < n_count; ++i) {
    int x_elem;
    cin >> x_elem;
    c_arr.push_back({x_elem, i});
  }
  std::sort(b_arr.rbegin(), b_arr.rend());
  std::sort(c_arr.begin(), c_arr.end());
  int a_ans = 0;
  int b_ans = (int)b_arr.size();
  int c_ans = (int)c_arr.size();
  bool found = false;
  for (int i = 0; i < (int)a_arr.size(); ++i) {
    int l_gr = 0;
    int r_gr = 0;
    a_ans = i;
    long long summ = s_count - a_arr[i].first;
    while (l_gr < (int)b_arr.size() && r_gr < (int)c_arr.size()) {
      if (b_arr[l_gr].first + c_arr[r_gr].first == summ) {
        if (b_arr[l_gr].second < b_ans ||
            (b_arr[l_gr].second == b_ans && c_arr[r_gr].second <= c_ans)) {
          b_ans = b_arr[l_gr].second;
          c_ans = c_arr[r_gr].second;
        }

        found = true;
        l_gr++;
        continue;
      }

      if (b_arr[l_gr].first + c_arr[r_gr].first > summ) {
        l_gr++;
      } else {
        r_gr++;
      }
    }
    if (found) {
      break;
    }
  }
  if (found) {
    cout << a_ans << ' ' << b_ans << ' ' << c_ans;
  } else {
    cout << -1;
  }
}
