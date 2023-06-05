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


void solve() {
    size_t n, m;
    cin >> n >> m;

    auto graph = vector<vector<size_t>>(n+1);
    auto in_degree = vector<size_t>(n+1, 0);
    for(auto i = size_t{0}; i < m; i++) {
        size_t u,v;
        cin >> u >> v;
        graph[u].push_back(v);
        in_degree[v]++;
    }

    if (has_cycle(graph)) {
        std::cout << "recheck hints" << endl;
        return;
    }

    auto q = queue<size_t>();
    auto starting_nodes = vector<size_t>();
    
    for(size_t node = 1; node <= n; node++) {
        if(in_degree[node] == 0) {
            starting_nodes.push_back(node);
            break;
        }
    }

    if (starting_nodes.size() > 1) {
        cout << "missing hints" << endl;
        return;
    }

    q.push(starting_nodes[0]);

    auto dp = vector<vector<size_t>>(n+1, vector<size_t>{});

    auto empty = vector<size_t>();
    auto longest_path = &empty;

    auto counter = size_t{0};

    while(!q.empty()) {
        cout << counter++ << endl;

        auto& node = q.front();
        q.pop();

        if (graph[node].size() == 0 && dp[node].size() >= longest_path->size()) {
            dp[node].push_back(node);
            longest_path = &dp[node];
        }

        for(const auto& neighbor : graph[node]) {
            in_degree[neighbor]--;
            if(in_degree[neighbor] == 0) {
                q.push(neighbor);
            }
            if (dp[neighbor].size() < (dp[node].size() + 1)) {
                auto v = dp[node];
                v.push_back(node);
                dp[neighbor] = v;
            }

            if (dp[neighbor].size() > longest_path->size()) {
                longest_path = &dp[neighbor];
            }
            
        }
    }

    if (longest_path->size() < n) {
        cout << "missing hints" << endl;
        return;
    }

    rep(i, longest_path->size()) {
        cout << longest_path->at(i) << " ";
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    uint cases;
    cin >> cases;
    rep (i, cases) {
        solve();
    }
}