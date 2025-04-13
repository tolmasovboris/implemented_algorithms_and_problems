#include <iostream>
using std::cin;
using std::cout;
using std::max;
const long long cModulo = 1e9;
struct Node {
  Node* left = nullptr;
  Node* right = nullptr;
  long long value = 0;
  int height = 0;
};
Node* NewNode(long long value) {
  Node* node = new Node();
  node->value = value;
  node->left = nullptr;
  node->right = nullptr;
  node->height = 0;
  return node;
}
int Height(Node* node) {
  if (node != nullptr) {
    return node->height;
  }
  return -1;
}
Node* RotateRight(Node*& cur) {
  if (cur->left != nullptr) {
    Node* left = cur->left;
    cur->left = left->right;
    left->right = cur;
    cur->height = max(Height(cur->left), Height(cur->right)) + 1;
    left->height = max(Height(left->left), cur->height) + 1;
    return left;
  }
  return cur;
}

Node* RotateLeft(Node*& cur) {
  if (cur->right != nullptr) {
    Node* right = cur->right;
    cur->right = right->left;
    right->left = cur;
    cur->height = max(Height(cur->left), Height(cur->right)) + 1;
    right->height = max(Height(cur->right), cur->height) + 1;
    return right;
  }
  return cur;
}

Node* RotateLeftBig(Node*& cur) {
  cur->right = RotateLeft(cur->right);
  return RotateLeft(cur);
}

Node* RotateRightBig(Node*& cur) {
  cur->left = RotateRight(cur->left);
  return RotateRight(cur);
}

Node* Find(Node* node, long long elem) {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->value == elem) {
    return node;
  }
  if (node->value > elem) {
    return Find(node->left, elem);
  }
  return Find(node->right, elem);
}

Node* Insert(Node* cur, long long x) {
  if (cur == nullptr ) {
    cur = NewNode(x);
  } else if (x < cur->value) {
    cur->left = Insert(cur->left, x);
    if (Height(cur->left) - Height(cur->right) == 2) {
      if (x < cur->left->value) {
        cur = RotateRight(cur);
      } else {
        cur = RotateRightBig(cur);
      }
    }
  } else if (x > cur->value) {
    cur->right = Insert(cur->right, x);
    if (Height(cur->right) - Height(cur->left) == 2) {
      if (x > cur->right->value) {
        cur = RotateLeft(cur);
      } else {
        cur = RotateLeftBig(cur);
      }
    }
  }

  cur->height = max(Height(cur->left), Height(cur->right)) + 1;
  return cur;
}
Node* LowerBound(Node* node, long long elem) {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->value >= elem) {
    Node* left_result = LowerBound(node->left, elem);
    return left_result != nullptr ? left_result : node;
  }
  return LowerBound(node->right, elem);
}
void Delete(Node* node) {
  if (node == nullptr) {
    return;
  }
  Delete(node->left);
  Delete(node->right);
  delete (node);
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int queries = 0;
  cin >> queries;
  char command;
  long long prev = 0;
  Node* root = nullptr;
  for (int i = 0; i < queries; ++i) {
    cin >> command;
    if (command == '+') {
      long long elem = 0;
      cin >> elem;
      if (prev != 0) {
        if (Find(root, elem + prev) == nullptr) {
          root = Insert(root, (elem + prev) % cModulo);
        }
      } else {
        if (Find(root, elem) == nullptr) {
          root = Insert(root, elem);
        }
      }
      prev = 0;
    }
    if (command == '?') {
      long long elem = 0;
      cin >> elem;
      prev = LowerBound(root, elem) != nullptr ? LowerBound(root, elem)->value
                                               : -1;
      cout << prev << '\n';
    }
  }

  Delete(root);
}
