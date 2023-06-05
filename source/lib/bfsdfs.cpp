#include <queue>
#include <vector>
#include <stack>

#define csize(a)     static_cast<size_t>(a)

using namespace std;
using ll = long long;

bool bfs(vector<vector<ll>> adjacent_matrix) {

    auto startNode  = size_t{0};
    auto seen       = vector<bool>(adjacent_matrix.size(), false);
    seen[startNode] = true;
    auto seen_elements = size_t{1};

    auto q          = queue<ll>();
    q.push(static_cast<ll>(startNode));

    while (!q.empty()) {
        auto node = q.front();
        q.pop();

        for (const auto& child : adjacent_matrix[csize(node)]) {
            if (!seen[size_t(child)]) {
                q.push(child);
                seen[csize(child)] = true;
                ++seen_elements;
            }
        }
    }

    return seen_elements == adjacent_matrix.size();
}

size_t dfs(vector<vector<ll>>& graph, ll start) {
    auto visited = vector<bool>(graph.size(), false);
    auto visited_elements = size_t{1};
    auto st = stack<ll>();

    st.push(start);
    visited[start] = true;

    while (!st.empty()) {
        int currentNode = st.top();
        st.pop();

        for (ll neighbor : graph[currentNode]) {
            if (!visited[neighbor]) {
                st.push(neighbor);
                visited[neighbor] = true;
                ++visited_elements;
            }
        }
    }

    return visited_elements;
}
