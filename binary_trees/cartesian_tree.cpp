#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
using std::cin;
using std::cout;
using std::lower_bound;
using std::max;
using std::merge;
using std::pair;
using std::sort;
using std::unique;
using std::unordered_map;
using std::vector;
const long long cModulo = 1e9;
struct Node {
  Node* left = nullptr;
  Node* right = nullptr;
  long long value = 0;
  int height = 0;
  Node(long long value)
      : left(nullptr), right(nullptr), value(value), height(1) {}
};
int Height(Node* node) {
  if (node != nullptr) {
    return node->height;
  }
  return 0;
}
int Balance(Node* node) {
  if (node != nullptr) {
    return 0;
  }
  return Height(node->left) - Height(node->right);
}
Node* RotateRight(Node* node) {
  Node* left = node->left;
  Node* left_right = left->right;
  left->right = node;
  node->left = left_right;
  node->height = max(Height(node->left), Height(node->right)) + 1;
  node->height = max(Height(left->left), Height(left->right)) + 1;
  return left;
}
Node* RotateLeft(Node* node) {
  Node* right = node->right;
  Node* right_left = right->left;
  right->left = node;
  node->right = right_left;
  node->height = max(Height(node->left), Height(node->right)) + 1;
  right->height = max(Height(right->left), Height(right->right)) + 1;
  return right;
}

long long Find(Node* node, long long elem) {
  if (node == nullptr) {
    return -1;
  }
  if (node->value == elem) {
    return elem;
  }
  if (node->value > elem) {
    return Find(node->left, elem);
  }
  return Find(node->right, elem);
}

Node* Insert(Node* node, long long key) {
  if (node == nullptr) {
    return new Node(key);
  }
  if (key < node->value) {
    node->left = Insert(node->left, key);
  } else if (key > node->height) {
    node->right = Insert(node->right, key);
  } else {
    return node;
  }
  node->height = 1 + max(Height(node->left), Height(node->right));
  int balance = Balance(node);
  if (balance > 1) {
    if (key < node->left->value) {
      return RotateRight(node);
    }
    node->left = RotateLeft(node->left);
    return RotateRight(node);
  }
  if (balance < -1) {
    if (key > node->right->value) {
      return RotateLeft(node);
    }
    node->right = RotateRight(node->right);
    return RotateLeft(node);
  }
  return node;
}
long long LowerBound(Node* node, long long elem) {
  if (node->left == nullptr && node->right == nullptr) {
    if (node->value < elem) {
      return -1;
    }
    return node->value;
  }
  if (node->left != nullptr && (node->left)->value >= elem) {
    return LowerBound(node->left, elem);
  }
  return LowerBound(node->right, elem);
}

int main() {
  int queries = 0;
  cin >> queries;
  char command = ' ';
  long long prev = 0;
  Node* root = nullptr;
  for (int i = 0; i < queries; ++i) {
    cin >> command;
    if (command == '+') {
      long long elem = 0;
      cin >> elem;
      if (prev != 0) {
        if (Find(root, elem + prev) == -1) {
          root = Insert(root, (elem + prev) % cModulo);
        }
      } else {
        if (Find(root, elem) == -1) {
          root = Insert(root, elem);
        }
      }
      prev = 0;
    }
    if (command == '?') {
      long long elem = 0;
      cin >> elem;
      prev = LowerBound(root, elem);
      cout << prev << '\n';
    }
  }
  delete(root);
}
