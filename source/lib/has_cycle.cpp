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
