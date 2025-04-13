#include <deque>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::deque;
using std::vector;
void Enqueue(deque<long long>& que, deque<long long>& min_que,
             long long x_elem) {
  while (!min_que.empty() && (x_elem < min_que.back())) {
    min_que.pop_back();
  }
  min_que.push_back(x_elem);
  que.push_back(x_elem);
}
void Clear(deque<long long>& que, deque<long long>& min_que) {
  que.clear();
  min_que.clear();
}
void Dequeue(deque<long long>& que, deque<long long>& min_que) {
  long long del = que.front();
  que.pop_front();
  if (del == min_que.front()) {
    min_que.pop_front();
  }
}
long long Min(deque<long long>& min_que) { return min_que.front(); }
int main() {
  int n_count = 0;
  int k_count = 0;
  deque<long long> que;
  deque<long long> min_que;
  cin >> n_count >> k_count;
  vector<vector<long long>> matrix(n_count);
  for (int i = 0; i < n_count; ++i) {
    for (int j = 0; j < n_count; ++j) {
      long long x_elem = 0;
      cin >> x_elem;
      matrix[i].push_back(x_elem);
    }
  }
  for (int i = 0; i < n_count; ++i) {
    for (int j = 0; j < k_count; ++j) {
      Enqueue(que, min_que, matrix[i][j]);
    }
    matrix[i][0] = Min(min_que);
    for (int j = 0; j < n_count - k_count; ++j) {
      Enqueue(que, min_que, matrix[i][k_count + j]);
      Dequeue(que, min_que);
      matrix[i][j + 1] = Min(min_que);
    }

    Clear(que, min_que);
  }
  for (int i = 0; i < n_count; ++i) {
    for (int j = 0; j < k_count; ++j) {
      Enqueue(que, min_que, matrix[j][i]);
    }
    matrix[0][i] = Min(min_que);
    for (int j = 0; j < n_count - k_count; ++j) {
      Enqueue(que, min_que, matrix[k_count + j][i]);
      Dequeue(que, min_que);
      matrix[j + 1][i] = Min(min_que);
    }

    Clear(que, min_que);
  }
  for (int i = 0; i < n_count - k_count + 1; ++i) {
    for (int j = 0; j < n_count - k_count + 1; ++j) {
      cout << matrix[i][j] << ' ';
    }
    cout << '\n';
  }
}
