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

using namespace std;

using ll = long long;
using ull = size_t;
using Graph = vector<vector<pair<size_t, size_t>>>;
using uint = uint32_t;

#define rep(a, b)   for(size_t a = 0; a < (b); ++a)
#define rep1(a, b)  for(size_t a = 1; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define endl        '\n'
#define cd(a)       static_cast<double>(a)
#define csize(a)     static_cast<size_t>(a)

struct Edge {
    int src, dest, weight;
};

struct Node {
    size_t index;
    size_t machine_cost;
};

// Structure to represent a disjoint set
struct DisjointSet {
    vector<int> parent, rank, costs;
    
    DisjointSet(int n, vector<int> c) {
        parent = vector<int>(n);
        rank = vector<int>(n, 0);
        costs = c;
        
        // Initially, each node is a separate set
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    
    // Find the parent of a node
    pair<int,int> find(int u) {
        if (parent[u] != u) {
            const auto& [ index, weight ] = find(parent[u]);
            parent[u] = index;
            costs[u] = weight;
        }
        return make_pair(parent[u], costs[u]);
    }
    
    // Union of two sets
    void merge(int u, int v) {
        u = find(u).first;
        v = find(v).first;
        
        // Take lower cost and add it to both.
        auto min_cost = min(costs[u], costs[v]);
        costs[u] = min_cost;
        costs[v] = min_cost;

        // Attach smaller rank tree under the root of higher rank tree
        if (rank[u] < rank[v]) {
            parent[u] = v;
        } else if (rank[u] > rank[v]) {
            parent[v] = u;
        } else {
            parent[v] = u;
            rank[u]++;
        }
    }
};

// Comparator function for sorting edges by their weight
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

// Function to find the MST using Kruskal's algorithm
ull kruskalMST(vector<Edge>& edges, int n, vector<int>& icecream_cost) {
    vector<Edge> result; // Stores the final MST
    
    // Sort edges in non-decreasing order of their weight
    sort(edges.begin(), edges.end(), compareEdges);
    DisjointSet ds(n, icecream_cost);
    
    // Process each edge in sorted order
    for (const auto& edge : edges) {
        const auto [ srcParent, costSrc ] = ds.find(edge.src);
        const auto [ destParent, costDest ] = ds.find(edge.dest);

        // If inserting the edge costs less, than keeping the larger of both costs, do it!
        // ... and inserting does not form a cycle.
        if (srcParent != destParent && edge.weight < max(costSrc, costDest)) {
            result.push_back(edge);
            ds.merge(srcParent, destParent);
        }
    }

    auto weight = ull{0};
    auto visited = vector<bool>(n, false);
    for (const auto& edge : result) {
        weight += edge.weight;
    }

    rep (i, n) {
        const auto [ parentIndex, parentWeight ] = ds.find(i);
        if (!visited[parentIndex]) {
            visited[parentIndex] = true;
            weight += parentWeight;
        } 
    }
    
    return weight;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    size_t nodes, edges;
    cin >> nodes >> edges;
    auto graph = vector<Edge>();

    auto icecream_costs = vector<int>(nodes);
    rep (i, icecream_costs.size()) {
        cin >> icecream_costs[i];
    }

    rep (i, edges) {
        int start, end, weight;
        cin >> start >> end >> weight;

        auto e = Edge{start, end, weight};
        auto e2 = Edge{end, start, weight};

        graph.push_back(e);
        graph.push_back(e2);
    }

    const auto cost = kruskalMST(graph, nodes, icecream_costs);

    cout << cost << endl;

    return 0;
}
