#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <stack>


#define rep(a, b)   for(size_t a = 0; a < (b); ++a)
#define rep1(a, b)  for(size_t a = 1; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define endl        '\n'
#define cd(a)       static_cast<double>(a)
#define csize(a)     static_cast<size_t>(a)

using ull = size_t;
struct Edge {
  ull start;
  ull end;
  ull capacity = 0;
  ull flow = 0;
  ull id;
};

using namespace std;
using ll = long long;
using Graph = vector<vector<Edge>>;
using uint = uint32_t;

void bfs(Graph& graph, unordered_set<ull>& res) {
  auto q = queue<ull>();
  auto visited = vector<bool>(graph.size(), false);
  q.push(1);

  while (!q.empty()) {
    auto f = q.front();
    q.pop();

    visited[f] = true;

    for (const auto& n : graph[f]) {
      if (n.capacity == 0) continue;

      if (n.capacity - n.flow == 0) {
        res.insert(n.id);
        continue;
      }

      if (!visited[n.end]) q.push(n.end);
    }
  }
}

ull dfs(Graph& graph) {
  auto s = stack<ull>();
  s.push(1);
  auto seen = vector<bool>(graph.size(), false);
  auto pred = vector<Edge*>(graph.size());

  while (!s.empty()) {
    const auto f = s.top();
    s.pop();

    for (auto ind = size_t{0}; ind < graph[f].size(); ++ind) {
      auto edge = graph[f][ind];

      if (edge.capacity - edge.flow == 0 || seen[edge.end]) continue;

      pred[edge.end] = &(graph[f][ind]);
      if (edge.end == graph.size() - 1) {
        auto minCapacity = SIZE_MAX;
        auto l = edge.end;

        // Find min flow capacity.
        while (l != 1) {
          minCapacity = min(minCapacity, pred[l]->capacity - pred[l]->flow);
          l = pred[l]->start;
        }

        // Increase all flows on this path.
        l = edge.end;
        while (l != 1) {
          pred[l]->flow += minCapacity;
          l = pred[l]->start;
        }

        return minCapacity;
      }
      seen[f] = true;
      s.push(edge.end);
    }
  }
  return 0;
}

void fordfulkerson(Graph& graph) {
  auto minCap = dfs(graph);
  auto totalFlow = ull{0};

  while (minCap > 0) {
    totalFlow += minCap;
    minCap = dfs(graph);
  }

  // Do bfs one last time to see, which nodes can still be reached.
  auto res = unordered_set<ull>();
  bfs(graph, res);

  cout << res.size() << " " << totalFlow << endl;
  for (const auto& r : res) {
    cout << r << " ";
  }
  cout << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);

  ull n,m;
  cin >> n >> m;
  auto graph = Graph(n+1);

  rep (i,m) {
    ull start, dest, capacity;
    cin >> start >> dest >> capacity;

    graph[start].push_back(Edge{start, dest, capacity, 0, i+1});
  }

  fordfulkerson(graph);
  return 0;
}
