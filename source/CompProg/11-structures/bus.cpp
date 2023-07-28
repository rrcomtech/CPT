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

ull aggregate (vector<ull>& patterns, ull sender, ull receiver) {
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

struct SegmentTree {
  ull _upper_bound;
  ull _lower_bound;
  ull _aggregate_value;

  SegmentTree* _left = nullptr;
  SegmentTree* _right = nullptr;

  explicit SegmentTree(ull lower_bound, ull upper_bound, vector<ull>& patterns)
    : _upper_bound(upper_bound), _lower_bound(lower_bound)
  {
    auto aggregate_value = aggregate(patterns, lower_bound, upper_bound);
    _aggregate_value = aggregate_value;

    const auto middle = (upper_bound + lower_bound) / 2;

    if (lower_bound != upper_bound) {
      auto left = new SegmentTree(lower_bound, middle, patterns);
      auto right = new SegmentTree(middle + 1, upper_bound, patterns);

      _left = left;
      _right = right;
    }
  }

  ~SegmentTree() {
    free(_left);
    free(_right);
  }

  ull range_query(ull query_lower, ull query_upper, vector<ull>& patterns) {
    // Perfectly matching intervals
    if (query_lower == _lower_bound && query_upper == _upper_bound) {
      return _aggregate_value;
    }

    // No intersection points between these two intervals.
    if (query_lower > query_upper || query_upper < _lower_bound || query_lower > _upper_bound) {
      return 0;
    }

    if (query_lower >= _left->_lower_bound && query_upper <= _left->_upper_bound) {
      // Query is totally in left Segment tree
      return _left->range_query(query_lower, query_upper, patterns);
    } else {
      if (query_lower >= _right->_lower_bound && query_upper <= _right->_upper_bound) {
        // Query is totally in right segment tree
        return _right->range_query(query_lower, query_upper, patterns);
      } else {
        // Query is partially in both segment trees
        const auto res_left = _left->range_query(query_lower, _left->_upper_bound, patterns);
        const auto res_right = _right->range_query(_right->_lower_bound, query_upper, patterns);

        const auto res = res_left ^ patterns[_left->_upper_bound] ^ res_right;
        return res;
      }
    }

    return 0;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);

  ull n, q;
  cin >> n >> q;

  auto patterns = vector<ull>(n+1, 0);

  rep (i, n) {
    cin >> hex >> patterns[i+1];
  }

  auto segment_tree = SegmentTree(1, n, patterns);

  rep (i, q) {
    ull start, dest;
    cin >> start >> dest;

    if (start >= dest) {
      const auto res1 = segment_tree.range_query(start, patterns.size() - 1, patterns);
      const auto res2 = segment_tree.range_query(1, dest, patterns);

      const auto res = res1 ^ patterns[patterns.size() - 1] ^ res2;
      cout << res << endl;

    } else {
      const auto res = segment_tree.range_query(start, dest, patterns);
      cout << res << endl;
    }
  }

  return 0;
}
