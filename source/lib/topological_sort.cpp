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
// Each edge is a pair of (target, weight).
using Graph = vector<vector<pair<size_t, size_t>>>;
using uint = uint32_t;

vector<ull> topological_sort(Graph graph) {
  const auto nodes = graph.size();

  auto incoming_nodes = Graph(nodes);
  auto degrees = vector<ull>(nodes, 0);
  auto visited = vector<bool>(graph.size(), false);
  auto costs = vector<ull>(nodes, 0);

  // Determine the degree of each node and their incoming edges.
  for (auto i = size_t{0}; i < graph.size(); ++i) {
    for (const auto& [ dest, weight ] : graph[i]) {
      incoming_nodes[dest].push_back(make_pair(i, weight));
      ++degrees[dest];
    }
  }

  // Insert all edges with no incoming edges (starting points). 
  auto q = queue<ull>();
  rep (i, degrees.size()) {
      if (degrees[i] == 0) {
          q.push(i);
      }
  }

  auto sorted_nodes = vector<ull>();
  while (!q.empty()) {
      auto degree0El = q.front();
      sorted_nodes.push_back(degree0El);
      q.pop();

      auto node_cost = ull{0};
      for (const auto& [origin, weight] : incoming_nodes[degree0El]) {
          node_cost = max(node_cost, weight + costs[origin]);
          
      }
      costs[degree0El] = node_cost;

      visited[degree0El] = true;
      for (const auto& [ind, weight] : graph[degree0El]) {
          --degrees[ind];
          if (degrees[ind] == 0) q.push(ind);
      }
  }

  return sorted_nodes;
}