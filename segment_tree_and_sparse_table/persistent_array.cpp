#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::pair;
using std::vector;
const int cNcount = 500000;
long long arr[cNcount];
struct SegmentTree {
  long long value;
  struct SegmentTree* left;
  struct SegmentTree* right;
};
SegmentTree* version[cNcount];
void Build(SegmentTree& tree, long long* v, int tl, int tr) {
  if (tl == tr) {
    tree.value = v[tl];
    tree.left = nullptr;
    tree.right = nullptr;
    return;
  }
  int mid = (tl + tr) / 2;
  tree.left = new SegmentTree();
  tree.right = new SegmentTree();
  Build(*tree.left, v, tl, mid);
  Build(*tree.right, v, mid + 1, tr);
}
long long Get(SegmentTree& v, int tl, int tr, int pos) {
  if (tl == tr) {
    return v.value;
  }
  int mid = (tl + tr) / 2;
  if (pos <= mid) {
    return Get(*v.left, tl, mid, pos);
  }
  return Get(*v.right, mid + 1, tr, pos);
}
void Update(SegmentTree& v, int tl, int tr, int pos, int val) {
  if (tl == tr) {
    v.value = val;
    return;
  }
  int mid = (tl + tr) / 2;
  if (pos <= mid) {
    SegmentTree* left = new SegmentTree();
    *left = *v.left;
    v.left = left;
    Update(*left, tl, mid, pos, val);
  } else {
    SegmentTree* right = new SegmentTree();
    *right = *v.right;
    v.right = right;
    Update(*right, mid + 1, tr, pos, val);
  }
}
void Create(int upd, int& pointer, int n_elems, int pos, long long value) {
  SegmentTree* node = new SegmentTree();
  *node = *version[upd - 1];
  version[pointer] = node;
  Update(*version[pointer++], 0, n_elems, pos, value);
}
int main() {
  int pointer = 1;
  int n_count = 0;
  cin >> n_count;
  for (int i = 1; i < n_count + 1; ++i) {
    long long x_elem = 0;
    cin >> x_elem;
    arr[i] = x_elem;
  }
  version[0] = new SegmentTree();
  Build(*version[0], arr, 0, n_count);
  int q_count = 0;
  cin >> q_count;
  for (int i = 0; i < q_count; ++i) {
    std::string command;
    cin >> command;
    if (command == "create") {
      int vers = 0;
      int pos = 0;
      long long val = 0;
      cin >> vers >> pos >> val;
      Create(vers, pointer, n_count, pos, val);
      continue;
    }
    if (command == "get") {
      int ver = 0;
      int index = 0;
      cin >> ver >> index;
      cout << Get(*version[ver - 1], 0, n_count, index) << '\n';
      continue;
    }
  }
}

