#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::string;
using std::vector;

int main() {
  string elems;
  getline(cin, elems);
  vector<char> stacks;
  for (int i = 0; i < (int)elems.size(); ++i) {
    stacks.push_back(elems[i]);
    while ((int)stacks.size() > 1) {
      if (stacks[stacks.size() - 1] == ']' &&
          stacks[stacks.size() - 2] == '[') {
        stacks.pop_back();
        stacks.pop_back();
        continue;
      }
      if (stacks[stacks.size() - 1] == '}' &&
          stacks[stacks.size() - 2] == '{') {
        stacks.pop_back();
        stacks.pop_back();
        continue;
      }
      if (stacks[stacks.size() - 1] == ')' &&
          stacks[stacks.size() - 2] == '(') {
        stacks.pop_back();
        stacks.pop_back();
        continue;
      }
      break;
    }
  }
  if ((int)stacks.size() == 0) {
    cout << "YES";
  } else {
    cout << "NO";
  }
}
