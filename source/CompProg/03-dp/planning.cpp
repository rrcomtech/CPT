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


#define rep(a, b)   for(uint a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define uint        uint32_t
#define endl        '\n'
#define cd(a)       static_cast<double>(a)

using namespace std;
using Graph = vector<vector<int>>;
using ll = long long;

vector<ll> getSequence(vector<ll> contests) {
    auto longest_order = vector<ll>(contests.size(), 0);
    auto orders = vector<vector<ll>>();
    rep (i, contests.size()) {
        auto longest = ll{0};
        const auto s = orders.size();
        rep (o, s) {
            const auto largest = orders[o][orders[o].size() - 1];
            if (largest < contests[i]) {
                longest = max(static_cast<ll>(orders[o].size()), longest);
                orders.push_back(orders[o]);
                orders[o].push_back(contests[i]);
            }
        }
        longest_order[i] = longest;
        orders.push_back({ contests[i] });
    }

    return longest_order;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    uint n;
    cin >> n;
    auto contests = vector<ll>(n);
    rep (i, n) {
        cin >> contests[i];
    }
    // Length and last number.
    auto increasing_orders = getSequence(contests);
    reverse(all(contests));
    auto decreasing_orders = getSequence(contests);
    reverse(all(decreasing_orders));

    auto l = ll{0};
    rep (i, decreasing_orders.size()) {
        l = max(increasing_orders[i] + decreasing_orders[i] + 1, l);
    }
    std::cout << l << endl;

    return 0;
}
