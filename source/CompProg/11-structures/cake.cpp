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

ull gcd(ull a, ull b){
  return !a ? b : gcd(b % a, a);
}

ull aggregate (const vector<ull>& weights, ull start, ull end) {
  auto next = (start + 1) % weights.size();
  auto g = gcd(weights[start], weights[next]);

  while (g != 1 && next != end) {
    next = (next + 1) % weights.size();
    g = gcd(g, weights[next]);
  }

  return g;
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
            tree[node] = arr[start];
            return;
        }

        auto mid = (start + end) / 2;
        auto left = 2 * node;
        auto right = 2 * node + 1;

        build(arr, left, start, mid);
        build(arr, right, mid + 1, end);
        tree[node] = gcd(tree[left], tree[right]);
    }

    void update(ull point, const vector<ull>& arr) {
        update(1, 0, n - 1, point, arr);
    }

    void update(ull node, ull start, ull end, ull point, const vector<ull>& arr) {
        if (start == end) {
            tree[node] = arr[point];
            return;
        }

        auto mid = (start + end) / 2;
        auto left_node = 2 * node;
        auto right_node = 2 * node + 1;

        if (point <= mid) {
          update(left_node, start, mid, point, arr);
        } else {
          update(right_node, mid + 1, end, point, arr);
        }

        tree[node] = gcd(tree[left_node], tree[right_node]);
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
            const auto r = query(2 * node + 1, mid + 1, end, qleft, qright);
            return r;
        }

        if (qright <= mid) {
            const auto l = query(2 * node, start, mid, qleft, qright);
            return l;
        }

        const auto l = query(2 * node, start, mid, qleft, mid);
        const auto r = query(2 * node + 1, mid + 1, end, mid + 1, qright);

        return gcd(l, r);
    }
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);

  ull n, q;
  cin >> n >> q;

  auto pieces = vector<ull>(n);
  rep (i, n) {
    cin >> pieces[i];
  }

  auto tree = SegmentTree(pieces);

  rep (_, q) {
    string type;
    cin >> type;

    if (type == "?") {
      // Range query
      ull l, r;
      cin >> l >> r; l--; r--;

      const auto res = tree.query(l, r);
      cout << res << endl;
    } else {
      // Point update
      string name;
      ull i,x;
      cin >> name >> i >> x; i--;
      pieces[i] -= x;
      tree.update(i, pieces);
    }
  }

  return 0;
}
