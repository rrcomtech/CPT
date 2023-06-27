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

void solve() {
  ull no_cities;
  cin >> no_cities;

  // Number of cities without duplicated cities.
  auto actual_cities = ll{0};

  auto cities = vector<pair<ll,ll>>();
  auto map = vector<vector<ll>>(1024, vector<ll>(1024, -1));
  rep (_, no_cities) {
    ll x,y;
    cin >> x >> y;

    if (map[x][y] == -1) {
      // ID for each city
      map[x][y] = actual_cities;
      cities.emplace_back(x, y);
      ++actual_cities;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);

  ull cases;
  cin >> cases;
  rep (_, cases) solve();

  return 0;
}
