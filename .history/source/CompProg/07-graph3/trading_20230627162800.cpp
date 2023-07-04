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
using Graph = vector<vector<double>>;
using uint = uint32_t;

bool bellman_ford(Graph& graph) {
  auto dist = vector<double>(graph.size(), SIZE_MAX);
  auto pred = vector<vector<ull>>();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);

  ull no_currencies;
  cin >> no_currencies;

  auto currencies = vector<string>(no_currencies);
  rep(i, no_currencies) {
    cin >> currencies[i];
  }

  auto graph = vector<vector<double>>(no_currencies, vector<double>(no_currencies));
  rep(from, no_currencies) {
    rep (to, no_currencies) {
      double er;
      cin >> er;
      graph[from][to] = er;
    }
  }



  return 0;
}
