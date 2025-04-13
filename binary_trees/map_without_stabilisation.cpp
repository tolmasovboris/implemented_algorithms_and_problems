#include <iostream>
#include <set>
#include <string>
using std::cin;
using std::cout;
using std::max;
using std::pair;
using std::string;
struct Node {
  Node* left = nullptr;
  Node* right = nullptr;
  string value;
  string ans;
  int height = 0;
};
Node* NewNode(string& value, string& ans) {
  Node* node = new Node();
  node->value = value;
  node->ans = ans;
  node->left = nullptr;
  node->right = nullptr;
  node->height = 0;
  return node;
}
int Height(Node*& node) {
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

Node* Find(Node*& node, string& elem) {
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

Node* Insert(Node*& cur, string& x, string& y) {
  if (cur == nullptr) {
    cur = NewNode(x, y);
  } else if (x < cur->value) {
    cur->left = Insert(cur->left, x, y);
    if (Height(cur->left) - Height(cur->right) == 2) {
      if (x < cur->left->value) {
        cur = RotateRight(cur);
      } else {
        cur = RotateRightBig(cur);
      }
    }
  } else if (x > cur->value) {
    cur->right = Insert(cur->right, x, y);
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
  Node* root_log = nullptr;
  Node* root_pas = nullptr;
  int n_count = 0;
  cin >> n_count;
  for (int i = 0; i < n_count; ++i) {
    string login;
    string pass;
    cin >> login >> pass;
    root_log = Insert(root_log, login, pass);
    root_pas = Insert(root_pas, pass, login);
  }
  int query = 0;
  cin >> query;
  Node* ans = nullptr;
  for (int i = 0; i < query; ++i) {
    string request;
    cin >> request;
    ans = Find(root_log, request);
    if (ans != nullptr) {
      cout << ans->ans << '\n';
      continue;
    }
    ans = Find(root_pas, request);
    cout << ans->ans << '\n';
  }
  Delete(root_log);
  Delete(root_pas);
}
