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
#define csize(a)    static_cast<size_t>(a)
#define ull         size_t

using namespace std;
using ll = long long;
using Graph = vector<vector<pair<size_t, size_t>>>;
using uint = uint32_t;

void solve() {
    ull nodes, edges;
    cin >> nodes >> edges;

    auto graph = Graph(nodes);
    auto incoming_nodes = Graph(nodes);
    auto degrees = vector<ull>(nodes, 0);
    rep (i, edges) {
        ull s, e, w;
        cin >> s >> e >> w;

        graph[s-1].push_back(make_pair(e-1, w));
        incoming_nodes[e-1].push_back(make_pair(s-1, w));
        ++degrees[e-1];
    }

    auto visited = vector<bool>(graph.size(), false);
    auto costs = vector<ull>(nodes, 0);

    auto q = queue<ull>();
    rep (i, degrees.size()) {
        if (degrees[i] == 0) {
            q.push(i);
        }
    }

    auto m = ull{0};
    while (!q.empty()) {
        auto degree0El = q.front();
        q.pop();

        auto node_cost = ull{0};
        for (const auto& [origin, weight] : incoming_nodes[degree0El]) {
            node_cost = max(node_cost, weight + costs[origin]);
            
        }
        costs[degree0El] = node_cost;
        m = max(m, costs[degree0El]);

        visited[degree0El] = true;
        for (const auto& [ind, weight] : graph[degree0El]) {
            --degrees[ind];
            if (degrees[ind] == 0) q.push(ind);
        }
    }

    cout << m << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    size_t t;
    cin >> t;

    rep(i,t) solve();

    return 0;
}
