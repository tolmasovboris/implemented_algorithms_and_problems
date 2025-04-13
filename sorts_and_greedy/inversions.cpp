#include <iostream>
#include <vector>
long long static ans = 0;
void Merge(std::vector<long long> left, std::vector<long long> right,
           std::vector<long long>& arr) {
  int left_el = 0;
  int right_el = 0;
  while (left_el < (int)left.size() || right_el < (int)right.size()) {
    if (right_el == (int)right.size() ||
        (left_el < (int)left.size() && left[left_el] <= right[right_el])) {
      arr[left_el + right_el] = left[left_el];
      left_el++;
      ans += right_el;
    } else {
      arr[left_el + right_el] = right[right_el];
      right_el++;
    }
  }
}
void MergeSort(std::vector<long long>& arr) {
  if (arr.size() == 1) {
    return;
  }
  int middle = arr.size() / 2;
  std::vector<long long> l_gr;
  std::vector<long long> r_gr;
  for (int i = 0; i < middle; ++i) {
    if (i < (int)arr.size()) {
      l_gr.push_back(arr[i]);
    }
  }
  for (int i = 0; i < (int)arr.size(); ++i) {
    if (middle + i < (int)arr.size()) {
      r_gr.push_back(arr[middle + i]);
    }
  }
  MergeSort(l_gr);
  MergeSort(r_gr);
  Merge(l_gr, r_gr, arr);
}
int main() {
  int n_count;
  std::cin >> n_count;
  std::vector<long long> nums;
  for (int i = 0; i < n_count; ++i) {
    long long elem;
    std::cin >> elem;
    nums.push_back(elem);
  }

  MergeSort(nums);
  std::cout << ans;
}
