#include <deque>
#include <iostream>
#include <set>
#include <string>
using std::cin;
using std::cout;
using std::deque;
using std::string;
void GetSize(deque<long long>& que) { cout << que.size() << '\n'; }
void Enqueue(deque<long long>& que, deque<long long>& min_que,
             long long x_elem) {
  if (que.empty()) {
    min_que.push_back(x_elem);
  } else {
    while (!min_que.empty() && (x_elem < min_que.back())) {
      min_que.pop_back();
    }
    min_que.push_back(x_elem);
  }
  que.push_back(x_elem);
  cout << "ok\n";
}
void Clear(deque<long long>& que, deque<long long>& min_que) {
  que.clear();
  min_que.clear();
  cout << "ok\n";
}
void Dequeue(deque<long long>& que, deque<long long>& min_que) {
  if (que.empty()) {
    cout << "error\n";
  } else {
    long long del = que.front();
    que.pop_front();
    if (del == min_que.front()) {
      min_que.pop_front();
    }
    cout << del << '\n';
  }
}
void Min(deque<long long>& min_que) {
  if (min_que.empty()) {
    cout << "error\n";
  } else {
    cout << min_que.front() << '\n';
  }
}
void Front(deque<long long>& que) {
  if (que.empty()) {
    cout << "error\n";
  } else {
    cout << que.front() << '\n';
  }
}
int main() {
  size_t n_count = 0;
  deque<long long> que;
  deque<long long> min_que;
  cin >> n_count;
  for (size_t i = 0; i < n_count; ++i) {
    string command;
    cin >> command;
    if (command == "size") {
      GetSize(que);
      continue;
    }
    if (command == "min") {
      Min(min_que);
      continue;
    }
    if (command == "front") {
      Front(que);
      continue;
    }
    if (command == "clear") {
      Clear(que, min_que);
      continue;
    }
    if (command == "enqueue") {
      long long elem = 0;
      cin >> elem;
      Enqueue(que, min_que, elem);
      continue;
    }
    if (command == "dequeue") {
      Dequeue(que, min_que);
      continue;
    }
  }
}
