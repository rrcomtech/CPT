#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>

using namespace std;

typedef pair<int, int> pii;

struct Edge {
    int dest;
    int weight;
};

void dijkstra(vector<vector<Edge>>& graph, vector<int>& dist, vector<int>& citiesReached, int n) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        auto currCity = pq.top().second;
        auto currDist = pq.top().first;
        pq.pop();

        if (currDist > dist[currCity])
            continue;

        dist[currCity] = currDist;
        citiesReached[currCity]++;

        for (const auto edge : graph[currCity]) {
            auto neighborCity = edge.dest;
            auto neighborDist = edge.weight;
            if (max(dist[currCity], neighborDist) < dist[neighborCity]) {
                dist[neighborCity] = max(dist[currCity], neighborDist);
                pq.push({dist[neighborCity], neighborCity});
            }
        }
    }
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<vector<Edge>> graph(n);
        for (int i = 0; i < m; i++) {
            int a, b, w;
            cin >> a >> b >> w;
            graph[a].push_back({b, w});
            graph[b].push_back({a, w});
        }

        vector<int> dist(n, INT_MAX);
        vector<int> citiesReached(n, 0);

        dijkstra(graph, dist, citiesReached, n);
        sort(dist.begin(), dist.end());

        int threshold = ceil(0.75 * (n - 1));

        const auto& min_costs = dist[threshold];
        cout << min_costs << endl;
    }

    return 0;
}
