#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace __gnu_pbds;
using std::cin;
using std::cout;
using std::less;
using std::lower_bound;
using std::merge;
using std::pair;
using std::sort;
using std::string;
using std::unique;
using std::vector;
typedef tree<pair<long long, long long>, null_type,
             less<pair<long long, long long>>, rb_tree_tag,
             tree_order_statistics_node_update>
    OrderedSet;
long long GetDiff(pair<long long, long long> pair) {
  return (pair.second - pair.first) * (pair.second - pair.first);
}
int main() {
  int n_count = 0;
  OrderedSet order_set;
  cin >> n_count;
  long long ans = 0;
  long long prev = 0;
  for (int i = 0; i < n_count; ++i) {
    int elem = 0;
    cin >> elem;
    order_set.insert({prev, prev + elem});
    ans += (elem * elem);
    prev = elem + prev;
  }
  int queries = 0;
  cin >> queries;
  cout << ans << '\n';
  for (int i = 0; i < queries; ++i) {
    int command = 0;
    cin >> command;
    if (command == 1) {
      long long elem = 0;
      cin >> elem;
      pair<long long, long long> an = *order_set.find_by_order(elem - 1);
      long long len = an.second - an.first;
      if (elem - 1 == 0) {
        ans -= GetDiff(an);
        pair<long long, long long> prev = *order_set.find_by_order(1);
        ans -= GetDiff(prev);
        order_set.erase(order_set.find_by_order(0));
        order_set.erase(order_set.find_by_order(0));
        order_set.insert({0, prev.second});
        ans += (prev.second) * (prev.second);
      } else if (elem == (long long)order_set.size()) {
        ans -= GetDiff(an);
        order_set.erase(order_set.find_by_order(order_set.size() - 1));
        pair<long long, long long> prev =
            *order_set.find_by_order(order_set.size() - 1);
        ans -= GetDiff(prev);
        order_set.erase(order_set.find_by_order(order_set.size() - 1));
        order_set.insert({prev.first, an.second});
        ans += GetDiff({prev.first, an.second});
      } else {
        ans -= GetDiff(an);
        pair<long long, long long> prev = *order_set.find_by_order(elem - 2);
        pair<long long, long long> next = *order_set.find_by_order(elem);
        ans -= GetDiff(prev);
        ans -= GetDiff(next);
        auto pr = order_set.find_by_order(elem - 2);
        auto nx = order_set.find_by_order(elem);
        order_set.erase(order_set.find_by_order(elem - 1));
        order_set.erase(pr);
        order_set.erase(nx);
        order_set.insert({prev.first, an.first + (len) / 2});
        order_set.insert({an.first + (len) / 2, next.second});
        ans += GetDiff({prev.first, an.first + (len) / 2});
        ans += GetDiff({an.first + (len) / 2, next.second});
      }

      // for (auto it = order_set.begin(); it != order_set.end(); ++it) {
      // pair<long long, long long> ans = *it;
      // cout << ans.first << ' ' << ans.second << '\n';
      //}
    } else {
      long long index = 0;
      cin >> index;
      pair<long long, long long> last = *order_set.find_by_order(index - 1);
      long long length = last.second - last.first;
      ans -= GetDiff(*order_set.find_by_order(index - 1));
      order_set.erase(order_set.find_by_order(index - 1));
      order_set.insert({last.first, last.first + length / 2});
      order_set.insert({last.first + length / 2, last.second});
      ans += GetDiff({last.first, last.first + length / 2});
      ans += GetDiff({last.first + length / 2, last.second});

      // for (auto it = order_set.begin(); it != order_set.end(); ++it) {
      //  pair<long long, long long> ans = *it;
      //  cout << ans.first << ' ' << ans.second << '\n';
      //}
    }
    cout << ans << '\n';
  }
}
