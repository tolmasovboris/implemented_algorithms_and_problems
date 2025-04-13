#include <iostream>
using std::cin;
using std::cout;
const int cNcount = 200001;
const int cKcount = 800004;
long long tree[cKcount];
long long arr[cNcount];
void Build(int tl, int tr, int index) {
  if (tl == tr) {
    tree[index] = arr[tl];
    return;
  }
  int mid = (tl + tr) / 2;
  Build(tl, mid, index * 2 + 1);
  Build(mid + 1, tr, index * 2 + 2);
  tree[index] = std::max(tree[index * 2 + 1], tree[index * 2 + 2]);
}
void Update(int tl, int tr, int index, int pos, long long value) {
  if (tl == tr) {
    tree[index] = value;
    arr[tl] = value;
    return;
  }
  int mid = (tl + tr) / 2;
  if (mid >= pos) {
    Update(tl, mid, index * 2 + 1, pos, value);
  } else {
    Update(mid + 1, tr, index * 2 + 2, pos, value);
  }
  tree[index] = std::max(tree[index * 2 + 1], tree[index * 2 + 2]);
}
int Find(int tl, int tr, int index, int i_index, long long x_elem) {
  // cout << tl << ' ' << tr << ' ' << index << ' ' << tree[index] <<  '\n';
  if (tl == tr) {
    if (tree[index] < x_elem) {
      return -1;
    }
    return tl;
  }
  int mid = (tl + tr) / 2;
  int left = Find(tl, mid, 2 * index + 1, i_index, x_elem);
  if (tree[2 * index + 1] >= x_elem) {
    return left;
  }
  return Find(mid + 1, tr, 2 * index + 2, i_index, x_elem);
}
int GetSumm(int tl, int tr, int index, int i_index, long long x_elem) {
  if (tr < i_index) {
    return -1;
  }
  if (i_index <= tl) {
    if (tree[index] >= x_elem) {
      return Find(tl, tr, index, i_index, x_elem);
    }
    return -1;
  }
  int mid = (tl + tr) / 2;
  int left = GetSumm(tl, mid, 2 * index + 1, i_index, x_elem);
  if (left != -1) {
    return left;
  }
  return GetSumm(mid + 1, tr, 2 * index + 2, i_index, x_elem);
}
int main() {
  int n_count = 0;
  int q_count = 0;
  cin >> n_count >> q_count;
  for (int i = 0; i < n_count; ++i) {
    long long elem = 0;
    cin >> elem;
    arr[i] = elem;
  }
  Build(0, n_count - 1, 0);
  for (int i = 0; i < q_count; ++i) {
    int command = 0;
    cin >> command;
    if (command == 0) {
      int pos = 0;
      int elem = 0;
      cin >> pos >> elem;
      Update(0, n_count - 1, 0, pos - 1, elem);
    } else {
      int index = 0;
      int x_elem = 0;
      cin >> index >> x_elem;
      int mx = GetSumm(0, n_count - 1, 0, index - 1, x_elem);
      if (-1 == mx) {
        cout << -1 << '\n';
      } else {
        cout << mx + 1 << '\n';
      }
    }
  }
}
