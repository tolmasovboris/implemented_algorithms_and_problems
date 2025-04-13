#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using std::cin;
using std::cout;
using std::lower_bound;
using std::merge;
using std::pair;
using std::sort;
using std::unique;
using std::unordered_map;
using std::vector;
const long long cNcount = 1e6 + 1;
long long fenwick[cNcount];
vector<long long> Compress(vector<long long> a) {
  vector<long long> b = a;
  sort(b.begin(), b.end());

  unordered_map<long long, long long> m;

  for (long long x : b) {
    if (static_cast<int>(m.contains(x)) == 0) {
      m[x] = m.size();
    }
  }

  for (long long& x : a) {
    x = m[x];
  }

  return a;
}
void Upd(long long p, long long x) {
  for (; p < cNcount; p = (p | (p + 1))) {
    fenwick[p] += x;
  }
}

int Sum(long long p) {
  long long res = 0;
  for (; p >= 0; p = (p & (p + 1)) - 1) {
    res += fenwick[p];
  }
  return res;
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  long long ans = 0;
  int n_count = 0;
  // Node* root = new Node();
  cin >> n_count;
  vector<long long> coordinates;
  vector<pair<long long, long long>> segments;
  for (int i = 0; i < n_count; ++i) {
    long long l_gr = 0;
    long long r_gr = 0;
    cin >> l_gr >> r_gr;
    coordinates.push_back(l_gr);
    coordinates.push_back(r_gr);
  }
  coordinates = Compress(coordinates);
  for (int i = 0; i < n_count * 2; i += 2) {
    segments.push_back({coordinates[i], coordinates[i + 1]});
    Upd(coordinates[i + 1], 1);
  }
  sort(segments.begin(), segments.end(),
       [](pair<long long, long long>& a, pair<long long, long long>& b) {
         return a.first < b.first ||
                (a.first == b.first && a.second > b.second);
       });
  int k = 1;
  for (int i = 0; i < n_count; ++i) {
    if (i + 1 < n_count && (segments[i].first == segments[i + 1].first &&
                            segments[i].second == segments[i + 1].second)) {
      Upd(segments[i].second, -1);
      k++;
      continue;
    }
    ans += k * (Sum(segments[i].second) - 1);
    Upd(segments[i].second, -1);
    k = 1;
  }
  cout << ans;
}
