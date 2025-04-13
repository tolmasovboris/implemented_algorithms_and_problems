#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using std::cin;
using std::cout;
using std::max;
using std::min;
using std::sort;
using std::vector;
const long long cNcount = 1e9;
struct Node {
  long long summ;
  Node* left;
  Node* right;
  Node() : summ(0), left(nullptr), right(nullptr) {}
};
long long GetSum(Node* node) { return (node != nullptr) ? node->summ : 0; }
void Update(Node* node, long long left, long long right, long long pos,
            long long val) {
  if (left == right) {
    node->summ += val;
    return;
  }
  int mid = (left + right) / 2;
  if (pos <= mid) {
    if (node->left == nullptr) {
      node->left = new Node();
    }
    Update(node->left, left, mid, pos, val);
  } else {
    if (node->right == nullptr) {
      node->right = new Node();
    }
    Update(node->right, mid + 1, right, pos, val);
  }
  node->summ = GetSum(node->left) + GetSum(node->right);
}
long long Get(Node* node, long long tl, long long tr, long long left,
              long long right) {
  if (left > right) {
    return 0;
  }
  if (left == tl && tr == right) {
    return node->summ;
  }
  long long mid = (tl + tr) / 2;
  long long s1 = (node->left != nullptr)
                     ? Get(node->left, tl, mid, left, min(mid, right))
                     : 0;
  long long s2 = (node->right != nullptr)
                     ? Get(node->right, mid + 1, tr, max(left, mid + 1), right)
                     : 0;
  return s1 + s2;
}
void Delete(Node* node) {
  if (node->left != nullptr) {
    Delete(node->left);
  }
  if (node->right != nullptr) {
    Delete(node->right);
  }
  delete node;
}
int main() {
  int q_count = 0;
  Node* root = new Node();
  cin >> q_count;
  for (int i = 0; i < q_count; ++i) {
    char command;
    cin >> command;
    if (command == '+') {
      long long elem = 0;
      cin >> elem;
      Update(root, 0, cNcount - 1, elem - 1, elem);
    } else {
      long long elem = 0;
      cin >> elem;
      cout << Get(root, 0, cNcount - 1, 0, elem - 1) << '\n';
    }
  }
  Delete(root);
}
