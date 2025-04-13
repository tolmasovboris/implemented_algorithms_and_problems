#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::string;
using std::swap;
using std::vector;
int main() {
  std::priority_queue<long long> my_min_heap;
  long long const cDelim = 1 << 30;
  long long n_count;
  long long k_count;
  cin >> n_count >> k_count;
  long long a_count;
  long long x_count;
  long long y_count;
  cin >> a_count >> x_count >> y_count;
  for (int i = 0; i < n_count; ++i) {
    a_count = (a_count * x_count + y_count) % cDelim;
    my_min_heap.push(a_count);
    if ((int)my_min_heap.size() > k_count) {
      my_min_heap.pop();
    }
  }
  vector<long long> result;
  while (!my_min_heap.empty()) {
    result.push_back(my_min_heap.top());
    my_min_heap.pop();
  }

  std::sort(result.begin(), result.end());

  for (size_t i = 0; i < result.size(); ++i) {
    cout << result[i] << ' ';
  }
}
