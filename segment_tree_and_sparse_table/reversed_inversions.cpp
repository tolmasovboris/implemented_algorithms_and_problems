#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::vector;
const int cNcount = 262144;
const int cKcount = 262144 * 4;
long long tree[cKcount];
long long arr[cNcount];
void Build(int tl, int tr, int index) {
  if (tl == tr) {
    tree[index] = 1;
    return;
  }
  int mid = (tl + tr) / 2;
  Build(tl, mid, index * 2 + 1);
  Build(mid + 1, tr, index * 2 + 2);
  tree[index] = tree[index * 2 + 1] + tree[index * 2 + 2];
}
int GetS(int tl, int tr, int index, int st, int end) {
  if (st > tr || end < tl) {
    return 0;
  }
  if (st <= tl && end >= tr) {
    return tree[index];
  }
  int mid = (tl + tr) / 2;
  int left = GetS(tl, mid, 2 * index + 1, st, end);
  int right = GetS(mid + 1, tr, 2 * index + 2, st, end);
  return left + right;
}
void Update(int tl, int tr, int index, int pos, int val) {
  if (tl == tr) {
    tree[index] = val;
    return;
  }
  int mid = (tl + tr) / 2;
  if (mid >= pos) {
    Update(tl, mid, index * 2 + 1, pos, val);
  } else {
    Update(mid + 1, tr, index * 2 + 2, pos, val);
  }
  tree[index] = tree[index * 2 + 1] + tree[index * 2 + 2];
}
int GetSumm(int tl, int tr, int index, int value) {
  if (tl == tr) {
    return tl;
  }

  int mid = (tl + tr) / 2;
  // cout << tree[index * 2 + 1] << ' ' <<  value << '\n';
  if (tree[index * 2 + 1] > value) {
    // cout << "dfgdf\n";
    return GetSumm(tl, mid, index * 2 + 1, value);
  }
  return GetSumm(mid + 1, tr, index * 2 + 2, value - tree[index * 2 + 1]);
}
void InversePermutation(vector<int>& arr) {
  vector<int> arr2(arr.size());
  for (int i = 0; i < (int)arr.size(); i++) {
    arr2[arr[i] - 1] = i + 1;
  }
  arr = arr2;
}
int main() {
  int k = 0;
  // int q_count = 0;
  //  cin >> n_count >> q_count;
  int elem = 0;
  // int prev = -1;
  while (cin >> elem) {
    arr[k] = elem;
    k++;
  }

  Build(0, k - 1, 0);
  std::vector<int> permutation(k);
  for (int i = 0; i < k; ++i) {
    int index = GetSumm(0, k - 1, 0, arr[i]);
    permutation[index] = i + 1;
    Update(0, k - 1, 0, index, 0);
  }
  InversePermutation(permutation);
  vector<int> ans(k);
  for (int i = 0; i < k; ++i) {
    ans[permutation[i] - 1] = GetS(0, k - 1, 0, permutation[i] - 1, k - 1);
    Update(0, k - 1, 0, permutation[i] - 1, 1);
  }
  for (int i = 0; i < k; ++i) {
    cout << ans[i] << ' ';
  }
}
