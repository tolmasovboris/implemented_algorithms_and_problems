#include <iostream>
#include <vector>
void Merge(std::vector<std::pair<long long, long long>> a_arr,
           std::vector<std::pair<long long, long long>> b_arr,
           std::vector<std::pair<long long, long long>>& to) {
  size_t i_count = 0;
  size_t j_count = 0;
  while (i_count < a_arr.size() || j_count < b_arr.size()) {
    if (j_count == b_arr.size() ||
        (i_count < a_arr.size() &&
         (a_arr[i_count].first < b_arr[j_count].first ||
          (a_arr[i_count].first == b_arr[j_count].first &&
           a_arr[i_count].second < b_arr[j_count].second)))) {
      to[i_count + j_count] = a_arr[i_count];
      ++i_count;
    } else {
      to[i_count + j_count] = b_arr[j_count];
      ++j_count;
    }
  }
}
void MergeSort(std::vector<std::pair<long long, long long>>& arr) {
  if (arr.size() < 2) {
    return;
  }
  size_t middle = arr.size() / 2;
  std::vector<std::pair<long long, long long>> l_gr;
  std::vector<std::pair<long long, long long>> r_gr;
  for (size_t i = 0; i < middle; ++i) {
    if (i < arr.size()) {
      l_gr.push_back(arr[i]);
    }
  }
  for (size_t i = 0; i < arr.size(); ++i) {
    if (middle + i < arr.size()) {
      r_gr.push_back(arr[middle + i]);
    }
  }
  MergeSort(l_gr);
  MergeSort(r_gr);
  Merge(l_gr, r_gr, arr);
}
int main() {
  int count_n;
  std::cin >> count_n;
  std::vector<std::pair<long long, long long>> nums;
  std::vector<std::pair<long long, long long>> scanlines;
  for (int i = 0; i < count_n; ++i) {
    long long l_gr = 0;
    long long r_gr = 0;
    std::cin >> l_gr >> r_gr;
    nums.push_back({l_gr, r_gr});
  }
  MergeSort(nums);
  scanlines.push_back(nums[0]);
  for (size_t i = 1; i < nums.size(); ++i) {
    if (scanlines[scanlines.size() - 1].second >= nums[i].first &&
        nums[i].second >= scanlines[scanlines.size() - 1].second) {
      long long l_gr = scanlines[scanlines.size() - 1].first;
      scanlines.pop_back();
      scanlines.push_back({l_gr, nums[i].second});
      continue;
    }
    if (nums[i].second <= scanlines[scanlines.size() - 1].second) {
    } else {
      scanlines.push_back({nums[i].first, nums[i].second});
    }
  }
  std::cout << scanlines.size() << '\n';
  for (size_t i = 0; i < scanlines.size(); ++i) {
    std::cout << scanlines[i].first << ' ' << scanlines[i].second << '\n';
  }
}
