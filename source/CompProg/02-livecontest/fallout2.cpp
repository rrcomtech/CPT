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
using Graph = vector<vector<ull>>;
using uint = uint32_t;

bool is_cyclic_helper(vector<vector<size_t>>& graph, size_t& current_node, vector<bool>& visited, vector<bool>& path) {
    visited[current_node] = true;
    path[current_node] = true;

    for (auto& neighbor : graph[current_node]) {
        if (!visited[neighbor]) {
            if (is_cyclic_helper(graph, neighbor, visited, path))
                return true;
        } else if (path[neighbor]) {
            return true;
        }
    }

    path[current_node] = false;
    return false;
}

bool has_cycle(vector<vector<size_t>>& graph) {
    auto visited = vector<bool>(graph.size(), false);
    auto path = vector<bool>(graph.size(), false);

    for (auto i = size_t{0}; i < graph.size(); ++i) {
        if (!visited[i]) {
            if (is_cyclic_helper(graph, i, visited, path))
                return true;
        }
    }

    return false;
}

ull backtrack_length(Graph graph, Graph incoming_edges, ull start_node) {
  auto n = start_node;
  auto steps = ull{0};

  while (true) {
    if (graph[n].size() > 1) return steps;

    
  }
}

vector<ull> topological_sort(Graph graph) {
  const auto nodes = graph.size();

  auto incoming_nodes = Graph(nodes);
  auto degrees = vector<ull>(nodes, 0);
  auto visited = vector<bool>(graph.size(), false);
  auto costs = vector<ull>(nodes, 0);

  // Determine the degree of each node and their incoming edges.
  for (auto i = size_t{0}; i < graph.size(); ++i) {
    for (const auto& dest : graph[i]) {
      incoming_nodes[dest].push_back(i);
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

      visited[degree0El] = true;
      for (const auto& ind : graph[degree0El]) {
          --degrees[ind];
          if (degrees[ind] == 0) q.push(ind);
      }
  }

  return sorted_nodes;
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.precision(10);

  ull nodes;
  std::cin >> nodes;

  auto graph = Graph(nodes);
  auto degrees = vector<ull>(nodes);
  auto incoming_edges = Graph(nodes);
  rep (i, nodes-1) {
    ull start,end;
    std::cin >> start >> end;
    
    graph[start-1].push_back(end-1);
    degrees[start-1]++;
    incoming_edges[end-1].push_back(start-1);
  }

  //if (has_cycle(graph)) std::cout << "Has cycle" << endl;
  auto res = topological_sort(graph);
  reverse(all(res));

  for (auto i = size_t{0}; i < res.size(); ++i) {
    const auto n = res[i];
    for (const auto& inc : incoming_edges[n]) {
      if (graph[inc].size() > 1) 
    }
  }

  auto results = vector<ull>(nodes);
  for (auto i = size_t{0}; i < nodes; ++i) {
    if (degrees[res[i]] == 0) {
      results[res[i]] = 
      continue;
    }

    const auto edges = graph[res[i]];
    auto m = ull{0};
    for (const auto& dest : edges) {
      m = max(m, results[dest]);
    }
    results[res[i]] = m + 1;
  }

  rep (i, results.size()) {
    std::cout << results[i] << " ";
  }
  std::cout << endl;

  return 0;
}
