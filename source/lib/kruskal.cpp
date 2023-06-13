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
using Graph = vector<vector<pair<size_t, size_t>>>;
using uint = uint32_t;

struct Edge {
    int src, dest, weight;
};

// Structure to represent a disjoint set
struct DisjointSet {
    vector<int> parent, rank;
    
    DisjointSet(int n) {
        parent = vector<int>(n);
        rank = vector<int>(n, 0);
        
        // Initially, each node is a separate set
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    
    // Find the parent of a node
    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }
    
    // Union of two sets
    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        
        // Attach smaller rank tree under the root of higher rank tree
        if (rank[u] < rank[v])
            parent[u] = v;
        else if (rank[u] > rank[v])
            parent[v] = u;
        else {
            parent[v] = u;
            rank[u]++;
        }
    }
};

// Comparator function for sorting edges by their weight
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight > b.weight;
}

// Function to find the MST using Kruskal's algorithm
vector<Edge> kruskalMST(vector<Edge>& edges, int n) {
    vector<Edge> result; // Stores the final MST
    
    // Sort edges in non-decreasing order of their weight
    sort(edges.begin(), edges.end(), compareEdges);
    
    DisjointSet ds(n);
    
    // Process each edge in sorted order
    for (const auto& edge : edges) {
        int srcParent = ds.find(edge.src);
        int destParent = ds.find(edge.dest);
        
        // If including this edge does not form a cycle, add it to the MST
        if (srcParent != destParent) {
            result.push_back(edge);
            ds.merge(srcParent, destParent);
        }
    }
    
    return result;
}