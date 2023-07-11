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

using namespace std;
using ull = size_t;
struct Edge {
  ull start;
  ull end;
  ull capacity = 0;
  ull flow = 0;
  ull id;
  pair<ull,ull> reverseEdge; // Location of reverse Edge in graph.
  bool isReverse;
};

using ll = long long;
using Graph = vector<vector<Edge>>;
using uint = uint32_t;

void bfs2(Graph& graph, vector<bool>& seen) {
  auto q = queue<ull>();
  q.push(1);

  while (!q.empty()) {
    auto f = q.front();
    q.pop();
    seen[f] = true;

    for (const auto& n : graph[f]) {
      if (n.capacity - n.flow == 0) continue;
      if (!seen[n.end]) q.push(n.end);
    }
  }
}

ull bfs(Graph& graph) {
  auto q = queue<ull>();
  auto pred = vector<Edge*>(graph.size(), nullptr);

  q.push(1);

  while (!q.empty()) {
    auto u = q.front();
    q.pop();

    if (u == graph.size() - 1) break;

    for (auto& edge : graph[u]) {
      if (pred[edge.end] == nullptr && edge.end != 1 && edge.capacity > edge.flow) {
        pred[edge.end] = &edge;
        q.push(edge.end);
      }
    }
  }

  auto flow = ull{0};
  if (pred[graph.size() - 1] != nullptr) {
    // Augmenting path found
    flow = SIZE_MAX;

    for (auto edge = pred[graph.size() - 1]; edge != nullptr; edge = pred[edge->start]) {
      flow = min(flow, edge->capacity - edge->flow);
    }

    for (auto edge = pred[graph.size() - 1]; edge != nullptr; edge = pred[edge->start]) {
      edge->flow = edge->flow + flow;
      auto& revEdge = graph[edge->reverseEdge.first][edge->reverseEdge.second];
      revEdge.flow = revEdge.flow - flow;
    }
  }

  return flow;
}

void fordfulkerson(Graph& graph, vector<ull>& degrees) {
  auto res = vector<ull>();
  auto minCap = bfs(graph);
  auto totalFlow = ull{0};

  while (minCap > 0) {
    totalFlow += minCap;
    minCap = bfs(graph);
  }

  auto seen = vector<bool>(graph.size(), false);
  bfs2(graph, seen);

  auto results = vector<ull>();
  for (const auto& edges : graph) {
    for (const auto& e : edges) {
      if (!e.isReverse && e.capacity - e.flow == 0 && seen[e.start] && !seen[e.end]) {
        results.push_back(e.id);
      }
    }
  }

  cout << results.size() << " " << totalFlow << endl;
  for (const auto& r : results) cout << r << " ";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);

  ull n,m;
  cin >> n >> m;
  auto graph = Graph(n+1);
  auto degrees = vector<ull>(graph.size(), 0);

  //auto edgesPresent = vector<vector<pair<ull,ull>>>(n+1, vector<pair<ull,ull>>(false, {0,0}));

  rep (i,m) {
    ull start, dest, capacity;
    cin >> start >> dest >> capacity;

    auto reverseEdge = Edge{dest, start, capacity, capacity, i+1, {start,graph[start].size()}, true};
    auto e = Edge{start, dest, capacity, 0, i+1, {dest,graph[dest].size()}, false};

    graph[start].push_back(e);
    graph[dest].push_back(reverseEdge);
    degrees[dest]++;
  }

  fordfulkerson(graph, degrees);
  return 0;
}
