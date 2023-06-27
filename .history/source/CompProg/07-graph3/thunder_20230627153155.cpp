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
  ull cities;
  cin >> cities;

  auto map = vector<vector<ll>>(1024, vector<ll>(1024, -1));
  rep (_, cities) {
    ll x,y;
    cin >> x >> y;

    if (map[x][y] == -1) {
      map[x][y] = number_of_citys;
      citys.emplace_back(x, y);
      ++number_of_citys;
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
