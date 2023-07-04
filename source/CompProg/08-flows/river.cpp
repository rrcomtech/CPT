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

using ull = size_t;
using namespace std;
using ll = long long;
using Graph = vector<vector<ull>>;
using uint = uint32_t;


// Returns the path and the max flow.
pair<vector<ull>, ull> bfs(Graph graph, vector<ull> capacities, ull start, ull target) {
  auto seen = vector<bool>(graph.size(), false);
  auto pred = vector<ull>(graph.size());
  seen[start] = true;

  auto q = queue<ull>();
  q.push(start);

  while (!q.empty()) {
    auto node = q.front();
    q.pop();

    for (const auto& n : graph[node]) {
      if (seen[n] || capacities[n] == 0) continue;

      pred[n] = node;
      seen[n] = true;
      q.push(n);

      if (n == target) {
        auto l = n;
        auto maxCapacity = SIZE_MAX;
        auto res = vector<ull>{};

        while (l != start) {
          maxCapacity = min(capacities[l], maxCapacity);

          if (pred[l] != 0) res.push_back(pred[l]);
          l = pred[l];
        }
        reverse(all(res));
        return make_pair(res, maxCapacity);
      }
    }
  }

  return make_pair(vector<ull>{}, 0);
}

void fordfulkerson(Graph& graph, vector<ull> capacities, ull start, ull target) {
  auto total_flow = ull{0};
  auto r = bfs(graph, capacities, start, target);
  auto p = r.first;
  auto maxFlow = r.second;

  while (!p.empty()) {
    total_flow += maxFlow;
    for (const auto& path_element : p) {
      capacities[path_element] -= maxFlow;
    }

    r = bfs(graph, capacities, start, target);
    p = r.first;
    maxFlow = r.second;
  }

  cout << total_flow << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);

  ull w, l;
  cin >> w >> l;

  auto graph = Graph(w + 1, vector<ull>(w + 1));
  auto capacities = vector<ull>(w+1);
  capacities[0] = SIZE_MAX;
  capacities[capacities.size()-1] = SIZE_MAX;
  rep1(pos, capacities.size() - 1) {
    cin >> capacities[pos];
  }

  rep(pos, graph.size()) {
    rep(adv, l+1) {
      auto dest = pos + adv;
      if (dest > w+1) dest = w+1; // At the other side of the river

      if (dest == w+1 || capacities[dest] > 0) {
        graph[pos].push_back(dest);
      }
    }
  }

  fordfulkerson(graph, capacities, 0, w);
  return 0;
}
