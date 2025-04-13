#include <cctype>
#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::string;
using std::vector;
int main() {
  string str;
  getline(cin, str);
  vector<long long> stacks;
  for (int i = 0; i < (int)str.size(); i++) {
    if (isdigit(str[i]) != 0) {
      stacks.push_back(str[i] - '0');
    } else if (str[i] == '-') {
      long long res = stacks[stacks.size() - 2] - stacks[stacks.size() - 1];
      stacks.pop_back();
      stacks.pop_back();
      stacks.push_back(res);
    } else if (str[i] == '*') {
      long long res = stacks[stacks.size() - 1] * stacks[stacks.size() - 2];
      stacks.pop_back();
      stacks.pop_back();
      stacks.push_back(res);
    } else if (str[i] == '+') {
      long long res = stacks[stacks.size() - 1] + stacks[stacks.size() - 2];
      stacks.pop_back();
      stacks.pop_back();
      stacks.push_back(res);
    }
  }
  cout << stacks[0];
}
