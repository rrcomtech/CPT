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

using namespace std;
using ll = long long;
using ull = size_t;
using Graph = vector<vector<pair<ull,ull>>>;
using uint = uint32_t;

vector<ull> djikstra(Graph graph) {
    auto visited = vector<bool>(graph.size(), false);
    auto costs = vector<ull>(graph.size(), SIZE_T_MAX);
    costs[0] = 0;
    visited[0] = true;
    auto c = 0;

    const auto compPair = [](pair<ull,ull> a, pair<ull,ull> b) {
        return a.second > b.second;
    };
    
    auto pq = priority_queue<pair<ull,ull>, vector<pair<ull,ull>>, decltype(compPair)>(compPair);
    pq.push(make_pair(0,0));

    while (!pq.empty()) {
        const auto node = pq.top().first;
        pq.pop();
        const auto& parent_costs = costs[node];

        for (const auto& neighbor : graph[node]) {
            const auto costFromThisDirection = max(neighbor.second, parent_costs);
            if (costFromThisDirection < costs[neighbor.first]) {
                costs[neighbor.first] = costFromThisDirection;

                if (costs[neighbor.first] <= 481428578) ++c;
            }

            if (!visited[neighbor.first]) {
                pq.push(make_pair(neighbor.first, neighbor.second));
                visited[neighbor.first] = true;
            }
        }
    }
    cout << "C: " << c << endl;

    return costs;
}

void solve() {
    ull nodes, edges;
    cin >> nodes >> edges;

    const auto nodes_share = cd(nodes) * double{0.75};
    const auto needed_nodes = csize(floor(nodes_share));

    auto graph = Graph(nodes);
    
    rep (i, edges) {
        ull start, end, weight;
        cin >> start >> end >> weight;

        graph[start].push_back(make_pair(end, weight));
        graph[end].push_back(make_pair(start, weight));
    }
    cout << "Needed: " << needed_nodes + 1 << endl;

    auto costs = djikstra(graph);
    sort(all(costs));

    const auto& min_costs = costs[needed_nodes];
    cout << min_costs << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    ull t;
    cin >> t;
    rep (i,t) solve();

    return 0;
}
