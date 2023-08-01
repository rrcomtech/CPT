#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <stack>
#include <bitset>
#include <sstream>
#include <array>


#define rep(a, b)   for(size_t a = 0; a < (b); ++a)
#define rep1(a, b)  for(size_t a = 1; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define endl        '\n'
#define cd(a)       static_cast<double>(a)
#define csize(a)     static_cast<size_t>(a)

using namespace std;
using ll = long long;
using ull = size_t;
using Graph = vector<vector<ll>>;
using uint = uint32_t;

ull aggregate (const vector<ull>& patterns, ull sender, ull receiver) {
  if (sender == receiver) return ull{0};

  auto number = patterns[sender];
  auto current = sender;
  auto next = (current + 1) % patterns.size();
  while (next != receiver) {
    number = number ^ patterns[next];
    next = (next + 1) % patterns.size();
  }

  return number;
}


class SegmentTree {
private:
    ull n;
    vector<ull> tree;
    vector<ull> weights;

public:
    SegmentTree(const vector<ull>& arr) {
        n = arr.size();
        weights = arr;
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }

    // Build the Segment Tree
    void build(const vector<ull>& arr, ull node, ull start, ull end) {
        if (start == end) {
            tree[node] = 0;
            return;
        }

        auto mid = (start + end) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        tree[node] = aggregate(arr, start, end);
    }

    // Query the minimum value in the range [left, right]
    ull query(ull left, ull right) {
        return query(1, 0, n - 1, left, right);
    }

    ull query(ull node, ull start, ull end, ull qleft, ull qright) {
        if (start == qleft && end == qright)
            return tree[node];

        if (start > qright || end < qleft)
          return 0;

        auto mid = (start + end) / 2;

        if (qleft > mid) {
          auto rightXOR = query(2 * node + 1, mid + 1, end, qleft, qright);
          return rightXOR;
        }

        if (qright <= mid) {
          auto leftXOR = query(2 * node, start, mid, qleft, qright);
          return leftXOR;
        }

        auto leftXOR = query(2 * node, start, mid, qleft, mid);
        auto rightXOR = query(2 * node + 1, mid + 1, end, mid + 1, qright);

        return leftXOR ^ weights[mid] ^ rightXOR;
    }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);

  ull n, q;
  cin >> n >> q;

  auto patterns = vector<ull>(n, 0);

  rep (i, n) {
    cin >> hex >> patterns[i];
  }

  auto segment_tree = SegmentTree(patterns);

  rep (i, q) {
    ull start, dest;
    cin >> dec >> start >> dest; start--; dest--;

    if (start >= dest) {
      const auto res1 = segment_tree.query(start, patterns.size() - 1);
      auto res2 = ull{0};
      if (dest != 0) {
        res2 = segment_tree.query(0, dest);
      }

      const auto res = res1 ^ patterns[n-1] ^ res2;
      cout << res << endl;

    } else {
      const auto res = segment_tree.query(start, dest);
      cout << res << endl;
    }
  }

  return 0;
}
