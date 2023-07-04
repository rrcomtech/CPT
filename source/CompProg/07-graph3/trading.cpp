#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <map>
#include <unordered_map>
#include <unordered_set>
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
using ull = size_t;
using Graph = vector<vector<double>>;
using uint = uint32_t;

struct Edge {
    ull start;
    ull dest;
    double rate;
};

vector<ull> findCycle(vector<ull> pred, ull start) {
    auto res = vector<ull>{start};

    auto c = ull{0};
    auto last_el = pred.at(start);
    while (last_el != start && c < pred.size() && last_el != pred.size() + 1) {
        if (last_el == start) break;

        res.push_back(last_el);
        last_el = pred.at(last_el);
        c++;
    }

    reverse(all(res));
    return res;
}

bool hasPred(ull start, ull target, vector<ull>& pred) {
    auto c = ull{0};
    auto last_el = pred[start];
    while (last_el != start && c < pred.size() && last_el != pred.size() + 1) {
        if (last_el == target) return true;
        last_el = pred[last_el];
        c++;
    }
    return false;
}

vector<ull> bellmanford(Graph& rates, vector<Edge>& edges) {
    auto cost = vector<double>(rates.size(), -1.0);
    auto pred = vector<ull>(rates.size(), rates.size() + 1);

    const auto start = ull{0};
    cost[start] = 1;

    auto cycle_element = ull{rates.size() + 1};

    rep (iteration, rates.size()) {
        auto done = false;
        for (const auto& edge : edges) {
            if (cost[edge.start] * edge.rate > cost[edge.dest]) {
                cost[edge.dest] = cost[edge.start] * edge.rate;
                pred[edge.dest] = edge.start;

                if (cost[edge.dest] > 1 && hasPred(edge.start, edge.dest, pred)) {
                    cycle_element = edge.dest;
                    done = true;
                    break;
                }
            }
        }
        if (done) break;
    }

    auto res = vector<ull>{};
    if (cycle_element != rates.size() + 1) {
        res = findCycle(pred, cycle_element);
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    ull c;
    cin >> c;

    auto currencies = vector<string>(c);
    rep (i, c) {
        cin >> currencies[i];
    }

    auto rates = Graph(c);
    auto edges = vector<Edge>();
    rep(i, c) {
        rep (j, c) {
            double r;
            cin >> r;
            r = exp(r);
            rates[i].push_back(r);

            edges.push_back(Edge{i, j, r});
        }
    }

    const auto negative_cycle = bellmanford(rates, edges);
    if (negative_cycle.empty()) {
        cout << "noglitch" << endl;
    } else {
        cout << "money!" << endl;
        cout << negative_cycle.size() << endl;
        for (const auto& path_el : negative_cycle) {
            cout << currencies[path_el] << " ";
        }
        cout << endl;
    }

    return 0;
}
