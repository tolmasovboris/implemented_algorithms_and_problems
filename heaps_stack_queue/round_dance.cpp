#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::string;
using std::vector;

int main() {
  vector<vector<int>> linked_list;
  vector<string> names;
  int n_count;
  cin >> n_count;
  for (int i = 0; i < n_count; ++i) {
    string elem;
    cin >> elem;
    names.push_back(elem);
  }
  for (int i = 0; i < n_count; ++i) {
    linked_list.push_back(
        {((n_count) + i - 1) % n_count, (i + 1) % n_count, i});
  }
  for (int i = 0; i < n_count - 3; ++i) {
    int x_dir = 0;
    cin >> x_dir;
    x_dir--;
    cout << names[linked_list[x_dir][0]] << ' ' << names[linked_list[x_dir][1]]
         << '\n';
    linked_list[linked_list[x_dir][0]][1] =
        linked_list[linked_list[x_dir][1]][2];
    linked_list[linked_list[x_dir][1]][0] =
        linked_list[linked_list[x_dir][0]][2];
  }
}
