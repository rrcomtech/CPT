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

// From lecture: Square & Multiply algorithm.
ll sm_pow(ll a, ll n) {
  if (n == 1) return a;

  auto result = sm_pow(a * a, n / 2);
  if (n % 2 != 0) result = result * a;
  return result;
}

bool even_a(ll n, ll b) {
  auto a_pow5 = n + sm_pow(b, 5);

  auto fifth_root = pow(cd(a_pow5), 1.0 / 5);
  if (floor(fifth_root) == fifth_root) {
    const auto a_out = static_cast<ll>(fifth_root);

    cout << a_out << " " << b << endl;
    return true;
  }
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);

  const auto MAX = ll{100'000};

  ll n;
  cin >> n;

  if (!even_a(n, 0)) {
    for (auto dist = ll{1}; dist < MAX; ++dist) {
      if (even_a(n, dist)) break;
      if (even_a(n, -dist)) break;
    }
  }

  return 0;
}
