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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);

  int k; cin >> k;

  auto edges = k*2 - 1;
  auto nodes = k*2;

  cout << nodes << " " << edges << " " << k << endl;
  rep(i, edges) {
    auto start = i + 1;
    auto dest = i + 2;
    auto weight = 5;
    if (i % 2 == 1) {
      weight = 1;
    }
    cout << start << " " << dest << " " << weight << endl;
  }

  return 0;
}
