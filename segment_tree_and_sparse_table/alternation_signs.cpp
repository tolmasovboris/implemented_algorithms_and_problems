#include <iostream>
using std::cin;
using std::cout;
const int cNcount = 100000;
const int cKcount = 400004;
int tree[cKcount];
int arr[cNcount];
void Build(int tl, int tr, int index) {
  if (tl == tr) {
    if (tl % 2 == 0) {
      tree[index] = arr[tl];
    } else {
      tree[index] = -arr[tl];
    }
    return;
  }
  int mid = (tl + tr) / 2;
  Build(tl, mid, index * 2 + 1);
  Build(mid + 1, tr, index * 2 + 2);
  tree[index] = tree[index * 2 + 1] + tree[index * 2 + 2];
}
void Update(int tl, int tr, int index, int pos, int value) {
  if (tl == tr) {
    if (tl % 2 == 0) {
      tree[index] = value;
    } else {
      tree[index] = -value;
    }
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
  int n_count = 0;
  cin >> n_count;
  for (int i = 0; i < n_count; ++i) {
    int elem = 0;
    cin >> elem;
    arr[i] = elem;
  }
  Build(0, n_count - 1, 0);
  int q_count = 0;
  cin >> q_count;
  for (int i = 0; i < q_count; ++i) {
    int command = 0;
    cin >> command;
    if (command == 0) {
      int pos = 0;
      int elem = 0;
      cin >> pos >> elem;
      Update(0, n_count - 1, 0, pos - 1, elem);
    } else {
      int left = 0;
      int right = 0;
      cin >> left >> right;
      int summ = GetSumm(0, n_count - 1, 0, left - 1, right - 1);
      if (left % 2 == 1) {
        cout << summ;
      } else {
        cout << -summ;
      }
      cout << '\n';
    }
  }
}
