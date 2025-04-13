#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;
const int cSize = 10000;
int fenvick[cSize][cSize];
void Update(int x, int y, int elems) {
  for (int i = x; i <= elems; i += i & -i) {
    for (int j = y; j <= elems; j += j & -j) {
      fenvick[i][j] += 1;
    }
  }
}
int Get(int x, int y) {
  int res = 0;
  for (int i = x; i > 0; i -= i & -i) {
    for (int j = y; j > 0; j -= j & -j) {
      res += fenvick[i][j];
    }
  }
  return res;
}
int main() {
  string command;
  int n_count = 0;
  int q_count = 0;
  cin >> n_count >> q_count;
  for (int i = 0; i < q_count; ++i) {
    cin >> command;
    if (command == "ADD") {
      int x_elem = 0;
      int y_elem = 0;
      cin >> x_elem >> y_elem;
      Update(x_elem, y_elem, n_count);
      continue;
    }
    if (command == "GET") {
      int x_1;
      int y_1;
      int x_2;
      int y_2;
      cin >> x_1 >> y_1 >> x_2 >> y_2;
      if (x_2 - x_1 < 0) {
        std::swap(x_1, x_2);
      }
      if (y_2 - y_1 < 0) {
        std::swap(y_1, y_2);
      }
      cout << Get(x_2, y_2) - Get(x_1 - 1, y_2) - Get(x_2, y_1 - 1) +
                  Get(x_1 - 1, y_1 - 1)
           << '\n';
      continue;
    }
  }
}
