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

struct Edge {
  ull start;
  ull dest;
  double cost;
}

bool bellman_ford(ull no_nodes, vector<Edge> edges) {
  auto dist = vector<double>(no_nodes, SIZE_MAX);
  auto pred = vector<ull>(no_nodes);

  const auto start = ull{0};
  dist[start] = 0;

  rep(it, no_nodes) {
    auto hasChanged = false;
    for (const auto& edge : edges) {
      const auto start = edge.start;
      const auto target = edge.dest;
      const auto length = edge.cost;

      if (dist[target] > dist[start] + length) {
        dist[target] = dist[start] + length;
        pred[target] = start;
        hasChanged = true;
      }
    }
  }

  return false;
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
