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

struct Edge {
    size_t start;
    size_t end;
    size_t cost;
};

struct Node {
    size_t index;
    size_t machine_cost;
};

using namespace std;
using ll = long long;
using Graph = vector<vector<pair<size_t, size_t>>>;
using uint = uint32_t;

void jarnik_prim(vector<vector<pair<size_t, size_t>>>& graph, size_t start, vector<bool>& visited, Graph& prevGraph) {
    size_t V = graph.size();

    priority_queue<
        pair<size_t, size_t>,
        vector<pair<size_t, size_t>>,
        greater<pair<size_t, size_t>>> pq;

    vector<size_t> weights(V, INT_MAX);
    vector<size_t> parent(V);
    vector<bool> inMST(V, false);

    pq.push(make_pair(start, 0));
    weights[start] = INT_MAX;
    visited[start] = true;

    while (!pq.empty()) {
        auto curr = pq.top().first;
        pq.pop();

        inMST[curr] = true;

        for (auto& neighbor : graph[curr]) {
            auto node = neighbor.first;
            auto weight = neighbor.second;

            if (weight < weights[node]) {
                weights[node] = weight;
                parent[node] = curr;
                if (!inMST[node]) {
                    pq.push(make_pair(node, weights[node]));
                }
            }
        }
    }

    rep1 (i, V) {
        if (inMST[i]) {
            auto found = false;
            for (const auto& neighbor : prevGraph[i]) {
                if (neighbor.first == parent[i]) {
                    found = true;
                    break;
                }
            } 

            if (!found) {
                visited[i] = true;
                prevGraph[i].push_back(make_pair(parent[i], weights[i]));
                prevGraph[parent[i]].push_back(make_pair(i, weights[i]));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    size_t nodes, edges;
    cin >> nodes >> edges;
    auto graph = Graph(nodes);

    auto icecream_costs = vector<Node>(nodes);
    rep (i, icecream_costs.size()) {
        size_t cost; 
        cin >> cost;

        Node n;
        n.index = i;
        n.machine_cost = cost;
        icecream_costs[i] = n;
    }

    rep (i, edges) {
        size_t start, end, weight;
        cin >> start >> end >> weight;

        graph[start].push_back(make_pair(end, weight));
        graph[end].push_back(make_pair(start, weight)); 
    }

    auto visited = vector<bool>(nodes, false);
    auto mst = Graph(nodes);
    jarnik_prim(graph, 0, visited, mst);

    rep (node, nodes) {
        if (!visited[node]) jarnik_prim(graph, node, visited, mst);
    }

    auto built_freezers = vector<size_t>(nodes, 0);
    

    return 0;
}
