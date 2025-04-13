#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::string;
using std::swap;
using std::vector;
void SiftUp(vector<vector<long long>>& arr, size_t index,
            vector<long long>& numbers) {
  if (index == 0) {
    return;
  }
  size_t new_pointer = (index - 1) / 2;
  if (arr[new_pointer][0] > arr[index][0]) {
    swap(arr[new_pointer], arr[index]);
    swap(numbers[arr[new_pointer][1]], numbers[arr[index][1]]);
    SiftUp(arr, new_pointer, numbers);
  }
}
void SiftDown(vector<vector<long long>>& arr, size_t index,
              vector<long long>& numbers) {
  if (2 * index + 1 >= arr.size()) {
    return;
  }
  size_t new_pointer = index * 2 + 1;
  if (new_pointer + 1 < arr.size() &&
      arr[new_pointer + 1][0] < arr[new_pointer][0]) {
    ++new_pointer;
  }
  if (arr[new_pointer][0] < arr[index][0]) {
    swap(arr[new_pointer], arr[index]);
    swap(numbers[arr[new_pointer][1]], numbers[arr[index][1]]);
    SiftDown(arr, new_pointer, numbers);
  }
}
void ExtractMin(vector<vector<long long>>& arr, vector<long long>& numbers) {
  swap(arr[arr.size() - 1], arr[0]);
  swap(numbers[arr[arr.size() - 1][1]], numbers[arr[0][1]]);
  arr.pop_back();
  SiftDown(arr, 0, numbers);
}
void Insert(vector<vector<long long>>& arr, vector<long long>& numbers) {
  SiftUp(arr, arr.size() - 1, numbers);
}
void DecreaseKey(vector<vector<long long>>& arr, long long decrease,
                 long long index, vector<long long>& numbers) {
  arr[index][0] -= decrease;
  SiftUp(arr, index, numbers);
}
int main() {
  vector<vector<long long>> my_heap;
  int querys;
  cin >> querys;
  vector<long long> numbers(querys);
  for (int i = 0; i < querys; ++i) {
    string command;
    cin >> command;
    if (command == "insert") {
      long long new_elem = 0;
      cin >> new_elem;
      my_heap.push_back({new_elem, i});
      numbers[i] = my_heap.size() - 1;
      SiftUp(my_heap, my_heap.size() - 1, numbers);
      continue;
    }
    if (command == "decreaseKey") {
      long long decr_elem = 0;
      cin >> decr_elem;
      long long decrease = 0;
      cin >> decrease;
      DecreaseKey(my_heap, decrease, numbers[decr_elem - 1], numbers);
      continue;
    }
    if (command == "getMin") {
      cout << my_heap[0][0] << '\n';
      continue;
    }
    if (command == "extractMin") {
      ExtractMin(my_heap, numbers);
      continue;
    }
  }
}
