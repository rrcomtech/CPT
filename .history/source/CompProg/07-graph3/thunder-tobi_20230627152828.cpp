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

#define all(a)      (a).begin(),(a).end()
#define endl        '\n'
#define int         int64_t
#define rep(a, b)   for(int a = 0; a < (b); ++a)

using namespace std;
using Graph = vector<vector<pair<int, double>>>;

double calculate_distance(pair<int, int> a, pair<int, int> b) {
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

bool is_reachable(int i, int j) {
    return calculate_distance(make_pair(0, 0), make_pair(i, j)) <= 10;
}

bool is_legit(int i, int j) {
    return i >= 0 && i < 1024 && j >= 0 && j < 1024;
}

bool check_if_connected(Graph& graph) {
    queue<int> q;
    vector<bool> visited(graph.size(), false);
    q.push(0);
    visited[0] = true;
    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        for (auto [a, b] : graph[current]) {
            if (!visited[a]) {
                visited[a] = true;
                q.push(a);
            }
        }
    }

    for (auto v : visited) {
        if (!v) {
            return false;
        }
    }

    return true;
}

pair<int, double> modified_dijkstra(Graph& graph, int start) {
    vector<double> distance(graph.size(), numeric_limits<double>::max());
    vector<bool> visited(graph.size(), false);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> q;
    q.push({0, start});
    distance[start] = 0;
    while (!q.empty()) {
        auto [current_distance, current_index] = q.top();
        q.pop();
        if (visited[current_index]) {
            continue;
        }
        visited[current_index] = true;
        for (auto [a, b] : graph[current_index]) {
            if (distance[a] > distance[current_index] + b) {
                distance[a] = distance[current_index] + b;
                q.push({distance[a], a});
            }
        }
    }

    double max_distance = 0;
    int max_index = 0;
    rep(i, distance.size()) {
        if (distance[i] > max_distance) {
            max_distance = distance[i];
            max_index = i;
        }
    }

    return {max_index, max_distance};
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    // cout << "test: " << calculate_distance(make_pair(int64_t{10}, int64_t{10}), make_pair(int64_t{13}, int64_t{14})) << endl;

    vector<pair<int, int>> reachable_fields;
    for (int i = -10; i <= 10; ++i) {
        for (int j = -10; j <= 10; ++j) {
            if (is_reachable(i, j)) {
                reachable_fields.emplace_back(i, j);
            }
        }
    }

    int number_of_test_cases;
    cin >> number_of_test_cases;

    rep(q, number_of_test_cases) {
        int temp_number_of_citys;
        cin >> temp_number_of_citys;

        vector<vector<int>> map(1024, vector<int>(1024, -1));
        vector<pair<int, int>> citys;

        int number_of_citys = 0;
        rep(z, temp_number_of_citys) {
            int x, y;
            cin >> x >> y;
            if (map[x][y] == -1) {
                map[x][y] = number_of_citys;
                citys.emplace_back(x, y);
                ++number_of_citys;
            }
        }

        Graph graph(number_of_citys);
        rep(i, number_of_citys) {
            auto [old_x, old_y] = citys[i];
            for (auto [a, b]: reachable_fields) {
                int new_x = old_x + a;
                int new_y = old_y + b;
                if (is_legit(new_x, new_y)) {
                    auto reached_index = map[new_x][new_y];
                    if (reached_index != -1 && reached_index != i) {
                        auto distance = calculate_distance(citys[i], citys[reached_index]);
                        graph[i].emplace_back(reached_index, distance);
                    }
                }
            }
        }

        if (!check_if_connected(graph)) {
            cout << "Send Kurdy" << endl;
        } else {
            auto res = double{0};

            // auto [i, egal] = modified_dijkstra(graph, 0);
            // auto [_, res] = modified_dijkstra(graph, i);

            rep(i, number_of_citys) {
                auto [_, new_res] = modified_dijkstra(graph, i);
                res = max(res, new_res);
            }

            cout << fixed;
            cout << setprecision(4);
            cout << res << endl;    
        }
    }

    return 0;
}
