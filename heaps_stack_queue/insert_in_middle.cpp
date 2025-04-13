#include <deque>
#include <iostream>
using std::cin;
using std::cout;
using std::deque;
void Middle(deque<int>& que, int x_elem) {
  auto it = que.begin();
  que.insert(it + static_cast<int>(((que.size() + 1) / 2)), x_elem);
}
int main() {
  deque<int> spec_que;
  int n_count = 0;
  cin >> n_count;
  for (int i = 0; i < n_count; ++i) {
    char command;
    cin >> command;
    if (command == '+') {
      int x_elem = 0;
      cin >> x_elem;
      spec_que.push_back(x_elem);
    } else if (command == '-') {
      int x_elem = 0;
      x_elem = spec_que.front();
      spec_que.pop_front();
      cout << x_elem << '\n';
    } else if (command == '*') {
      int x_elem = 0;
      cin >> x_elem;
      Middle(spec_que, x_elem);
    }
  }
}
