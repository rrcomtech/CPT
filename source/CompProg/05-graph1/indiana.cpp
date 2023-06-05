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

    for (int neighbor : graph[current_node]) {
        if (!visited[neighbor]) {
            if (is_cyclic_helper(graph, neighbor, visited, path))
                return true;
        } else if (path[neighbor]) {
            return true;
        }
    }

    // Backtrack
    path[current_node] = false;
    return false;
}

bool has_cycle(vector<vector<size_t>>& graph) {
    auto visited = vector<bool>(graph.size(), false);
    auto path = vector<bool>(graph.size(), false);

    for (ll i = 0; i < graph.size(); ++i) {
        if (!visited[i]) {
            if (is_cyclic_helper(graph, i, visited, path))
                return true;
        }
    }

    return false;
}


void solve() {
    ll n, h;
    cin >> n >> h;

    auto graph = Graph(n);
    auto starting_node_possibilities = vector<bool>(n, true);
    rep(i, csize(h)) {
        size_t pull_first, pull_second;
        cin >> pull_first >> pull_second;

        graph[pull_first - 1].push_back(pull_second - 1);
        starting_node_possibilities[pull_second - 1] = false;
    }

    if (has_cycle(graph)) {
        std::cout << "recheck hints" << endl;
        return;
    }

    auto starting_nodes = vector<ll>(-1);
    rep(i, starting_node_possibilities.size()) {
        if (starting_node_possibilities[i]) {
            starting_nodes.push_back(i);
        }
    }

    if (starting_nodes.size() > 1) {
        std::cout << "missing hints" << endl;
        return;
    }

    auto dp = vector<vector<size_t>>(n+1, vector<size_t>{});

    auto empty = vector<size_t>();
    auto longest_path = &empty;

    auto q = queue<size_t>();
    q.push(starting_nodes[0]);
    auto seen = vector<bool>(n+1, false);
    auto seen_elements = size_t{0};

    while(!q.empty()) {
        auto node = q.front();
        q.pop();

        if (graph[node].size() == 0 && dp[node].size() >= longest_path->size()) {
            dp[node].push_back(node);
            longest_path = &dp[node];
        }

        for(const auto& neighbor : graph[node]) {
            if (!seen[neighbor]) {
                seen[neighbor] = true;
                ++seen_elements;
            }

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

    if (visited_elements == g.size() && !multiple_possibilities) {
        rep(i, path.size()) std::cout << path[i] + 1 << " ";
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
