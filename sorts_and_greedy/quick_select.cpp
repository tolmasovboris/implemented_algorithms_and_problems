#include <iostream>
#include <vector>
int const cModulo = 1e7 + 4321;
int const cFirst = 45;
int const cSecond = 123;
size_t Partition(std::vector<int>& arr, size_t l_gr, size_t r_gr) {
  int x = arr[r_gr];
  int i = l_gr;
  for (size_t j = l_gr; j <= r_gr - 1; j++) {
    if (arr[j] <= x) {
      std::swap(arr[i], arr[j]);
      i++;
    }
  }
  std::swap(arr[i], arr[r_gr]);
  return i;
}

size_t QuickSelect(std::vector<int>& arr, size_t l_gr, size_t r_gr, size_t k) {
  size_t index = Partition(arr, l_gr, r_gr);
  if (index - l_gr == k - 1) {
    return arr[index];
  }
  if (index - l_gr > k - 1) {
    return QuickSelect(arr, l_gr, index - 1, k);
  }
  return QuickSelect(arr, index + 1, r_gr, k - index + l_gr - 1);
}

int main() {
  int n_count = 0;
  size_t k_count = 0;
  int elem1 = 0;
  int elem2 = 0;
  std::cin >> n_count >> k_count >> elem1 >> elem2;
  std::vector<int> nums;
  nums.push_back(elem1);
  nums.push_back(elem2);
  for (int i = 2; i < n_count; ++i) {
    nums.push_back((nums[i - 1] * cSecond + nums[i - 2] * cFirst) % cModulo);
  }
  std::cout << QuickSelect(nums, 0, n_count - 1, k_count);
}

