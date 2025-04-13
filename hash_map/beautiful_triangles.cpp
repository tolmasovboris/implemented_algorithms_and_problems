#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
const int cHash = 100003;

struct Point {
  long long x;
  long long y;

  Point(int x, int y) : x(x), y(y) {}

  long long SquaredDistance(const Point& other) const {
    return (long long)(x - other.x) * (x - other.x) +
           (long long)(y - other.y) * (y - other.y);
  }
};

class HashMap {
 private:
  struct Node {
    long long key;
    long long count;
    Node* next;

    Node(long long key) : key(key), count(1), next(nullptr) {}
    ~Node() { delete next; }
  };

  vector<Node*> table_;
  long long table_size_;

  long long HashFunction(long long key) const { return key % table_size_; }

 public:
  HashMap(long long size) : table_size_(size) { table_.resize(size, nullptr); }

  void Insert(long long key) {
    long long index = HashFunction(key);
    Node* current = table_[index];

    while (current != nullptr) {
      if (current->key == key) {
        current->count++;
        return;
      }
      current = current->next;
    }

    Node* new_node = new Node(key);
    new_node->next = table_[index];
    table_[index] = new_node;
  }

  long long GetCount(long long key) {
    long long index = HashFunction(key);
    Node* current = table_[index];

    while (current != nullptr) {
      if (current->key == key) {
        return current->count;
      }
      current = current->next;
    }

    return 0;
  }

  ~HashMap() {
    for (auto* node : table_) {
      delete node;
    }
  }
};

int main() {
  size_t n;
  short t;
  cin >> n >> t;

  vector<Point> points;
  for (size_t i = 0; i < n; i++) {
    long long x;
    long long y;
    cin >> x >> y;
    points.emplace_back(x, y);
  }

  long long triangle_count = 0;

  for (size_t i = 0; i < n; i++) {
    HashMap hash_map(cHash);

    for (size_t j = 0; j < n; j++) {
      if (i != j) {
        long long dist = points[i].SquaredDistance(points[j]);
        hash_map.Insert(dist);
      }
    }

    for (size_t j = 0; j < n; j++) {
      if (i != j) {
        long long dist = points[i].SquaredDistance(points[j]);
        long long count = hash_map.GetCount(dist);

        if (t == 1) {
          triangle_count += (count - 1);
        } else if (t == 2) {
          triangle_count = 0;
        }
      }
    }
  }

  cout << triangle_count / 2 << endl;
}
