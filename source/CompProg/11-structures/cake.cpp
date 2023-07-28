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

  explicit SegmentTree(ull lower_bound, ull upper_bound, function<ull(ull, ull)> agg)
          : _upper_bound(upper_bound), _lower_bound(lower_bound)
  {
    _aggregate_value = agg(lower_bound, upper_bound);

    const auto middle = (upper_bound + lower_bound) / 2;

    if (lower_bound != upper_bound) {
      _left = new SegmentTree(lower_bound, middle, agg);
      _right = new SegmentTree(middle + 1, upper_bound, agg);
    }
  }

  ~SegmentTree() {
    free(_left);
    free(_right);
  }

  ull point_update(ull index, ull subtraction) {

  }

  ull range_query(ull query_lower, ull query_upper) {

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

  auto gcd = [&pieces](ull l, ull r) {
    return ull{0};
  };

  auto tree = SegmentTree(1, n, gcd);

  rep (_, q) {
    string type;
    cin >> type;

    if (type == "?") {
      // Range query
      ull l, r;
      cin >> l >> r;

      const auto res = tree.range_query(l, r);
      cout << res << endl;

    } else {
      string name;
      ull i,x;
      cin >> name >> i >> x;


    }
  }

  return 0;
}
