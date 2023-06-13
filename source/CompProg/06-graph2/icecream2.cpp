#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Structure to represent a pipe connection
struct Pipe {
    int room1;
    int room2;
    int cost;

    Pipe(int r1, int r2, int c) : room1(r1), room2(r2), cost(c) {}
};

// Comparator for sorting pipe connections based on cost
bool comparePipes(const Pipe& p1, const Pipe& p2) {
    return p1.cost < p2.cost;
}

int findCheapestIceCreamCost(int n, int m, vector<int>& ci, vector<Pipe>& pipes) {
    // Sort pipe connections based on cost
    sort(pipes.begin(), pipes.end(), comparePipes);

    vector<long long> dp(n, INT_MAX); // Minimum cost to have ice cream in each room
    dp[0] = ci[0];

    for (const Pipe& pipe : pipes) {
        int room1 = pipe.room1;
        int room2 = pipe.room2;
        int cost = pipe.cost;

        dp[room2] = min(dp[room2], dp[room1] + cost);
    }

    long long minCost = dp[n - 1];

    // Consider building freezers in each room individually
    for (int i = 0; i < n; i++) {
        minCost = min(minCost, dp[i] + ci[i]);
    }

    return minCost;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> ci(n); // Costs of building freezers in each room
    for (int i = 0; i < n; i++)
        cin >> ci[i];

    vector<Pipe> pipes; // Pipe connections
    for (int i = 0; i < m; i++) {
        int a, b, p;
        cin >> a >> b >> p;
        pipes.push_back(Pipe(a, b, p));
    }

    long long cheapestCost = findCheapestIceCreamCost(n, m, ci, pipes);
    cout << cheapestCost << endl;

    return 0;
}