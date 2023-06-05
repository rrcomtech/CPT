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
using Graph = vector<vector<size_t>>;
using uint = uint32_t;

bool is_cyclic_helper(vector<vector<size_t>>& graph, size_t current_node, vector<bool>& visited, vector<bool>& path) {
    visited[current_node] = true;
    path[current_node] = true;

    for (const auto& neighbor : graph[current_node]) {
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

    for (auto i = ll{0}; i < graph.size(); ++i) {
        if (!visited[i]) {
            if (is_cyclic_helper(graph, i, visited, path))
                return true;
        }
    }

    return false;
}

vector<size_t> hamilton_path(vector<vector<size_t>> graph, size_t node) {
    auto o = vector<size_t>{node};

    if (graph[node].size() == 0) return o;

    auto longest_path = vector<size_t>();
    for (const auto& child : graph[node]) {
        auto path = hamilton_path(graph, child);
        if (longest_path.size() < path.size()) longest_path = path;
    }

    o.insert(o.end(), all(longest_path));
    return o;
}


void solve() {
    ll n, h;
    cin >> n >> h;

    auto g = Graph(n);
    auto starting_node_possibilities = vector<bool>(n, true);
    rep(i, csize(h)) {
        size_t pull_first, pull_second;
        
        cin >> pull_first >> pull_second;

        g[pull_first - 1].push_back(pull_second - 1);
        starting_node_possibilities[pull_second - 1] = false;
    }

    if (has_cycle(g)) {
        std::cout << "recheck hints" << endl;
        return;
    }

    auto starting_nodes = vector<ll>();
    rep(i, starting_node_possibilities.size()) {
        if (starting_node_possibilities[i]) {
            starting_nodes.push_back(i);
        }
    }

    if (starting_nodes.size() > 1) {
        std::cout << "missing hints" << endl;
        return;
    }
    
    auto path = hamilton_path(g, starting_nodes[0]);

    if (path.size() == g.size()) {
        for (const auto& p : path) std::cout << (p+1) << " ";
        std::cout << endl;
        return;
    }

    std::cout << "missing hints" << endl;
    return;
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    size_t cases;
    cin >> cases;

    rep (i, cases) solve();

    return 0;
}
