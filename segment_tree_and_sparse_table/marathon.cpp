#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::string;
using std::vector;
const int cNcount = 42196;
const int cPlayers = 100001;
const int cPrecision = 6;
int tree[cNcount * 4];
int arr[cNcount];
void Build(int tl, int tr, int index) {
  if (tl == tr) {
    tree[index] = arr[tl];
    return;
  }
  int mid = (tl + tr) / 2;
  Build(tl, mid, index * 2 + 1);
  Build(mid + 1, tr, index * 2 + 2);
  tree[index] = tree[index * 2 + 1] + tree[index * 2 + 2];
}
void Update(int tl, int tr, int index, int pos, int value) {
  if (tl == tr) {
    tree[index] += value;
    return;
  }
  int mid = (tl + tr) / 2;
  if (mid >= pos) {
    Update(tl, mid, index * 2 + 1, pos, value);
  } else {
    Update(mid + 1, tr, index * 2 + 2, pos, value);
  }
  tree[index] = tree[index * 2 + 1] + tree[index * 2 + 2];
}
int GetSumm(int tl, int tr, int index, int st, int end) {
  if (st > tr || end < tl) {
    return 0;
  }
  if (st <= tl && end >= tr) {
    return tree[index];
  }
  int mid = (tl + tr) / 2;
  int left = GetSumm(tl, mid, 2 * index + 1, st, end);
  int right = GetSumm(mid + 1, tr, 2 * index + 2, st, end);
  return left + right;
}
int main() {
  vector<int> cur_positions(cPlayers, 0);
  int q_count = 0;
  cin >> q_count;
  int participations = 0;
  Build(0, cNcount - 1, 0);
  for (int i = 0; i < q_count; ++i) {
    string command;
    cin >> command;
    if (command == "CHEER") {
      int index = 0;
      cin >> index;
      if (cur_positions[index] == 0) {
        cout << 0 << '\n';
        continue;
      }
      int reached = GetSumm(0, cNcount - 1, 0, 0, cur_positions[index] - 1);
      if (reached == 0 && participations == 1) {
        cout << 1 << '\n';
        continue;
      }
      if (reached == 0 && participations - 1 == 0) {
        cout << 0 << '\n';
        continue;
      }
      std::cout << std::fixed << std::setprecision(cPrecision);
      std::cout << static_cast<double>(reached) / (participations - 1) << '\n';
    }
    if (command == "RUN") {
      bool neu = false;
      int index = 0;
      int dist = 0;
      cin >> index >> dist;
      if (cur_positions[index] == 0) {
        participations++;
        neu = true;
      }

      if (!neu) {
        Update(0, cNcount - 1, 0, cur_positions[index], -1);
      }
      cur_positions[index] = dist;

      Update(0, cNcount - 1, 0, cur_positions[index], 1);
    }
  }
}
