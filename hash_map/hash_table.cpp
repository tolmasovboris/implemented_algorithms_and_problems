#include <iostream>
#include <vector>

const int cTableSize = 100003;
int Hash(int x) { return x % cTableSize; }

void Add(int x, std::vector<int>& table, std::vector<bool>& occupied) {
  int index = Hash(x);
  while (occupied[index] && table[index] != x) {
    index = (index + 1) % cTableSize;
  }
  table[index] = x;
  occupied[index] = true;
}

void Remove(int x, std::vector<int>& table, std::vector<bool>& occupied) {
  int index = Hash(x);
  while (occupied[index]) {
    if (table[index] == x) {
      occupied[index] = false;
      return;
    }
    index = (index + 1) % cTableSize;
  }
}

bool Find(int x, std::vector<int>& table, std::vector<bool>& occupied) {
  int index = Hash(x);
  while (occupied[index]) {
    if (table[index] == x) {
      return true;
    }
    index = (index + 1) % cTableSize;
  }
  return false;
}

int main() {
  int q;
  std::cin >> q;
  std::vector<int> table(cTableSize, 0);
  std::vector<bool> occupied(cTableSize, false);

  for (int i = 0; i < q; ++i) {
    char operation;
    int x;
    std::cin >> operation >> x;

    if (operation == '+') {
      Add(x, table, occupied);
    } else if (operation == '-') {
      Remove(x, table, occupied);
    } else if (operation == '?') {
      if (Find(x, table, occupied)) {
        std::cout << "YES\n";
      } else {
        std::cout << "NO\n";
      }
    }
  }
}
