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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    uint t;
    cin >> t;

    auto tsteps = vector<uint>(t);

    rep(i, t) {
        auto debt = uint32_t{0};
        auto no_coin_values = uint{0};
        cin >> debt >> no_coin_values;

        // Are sorted by concept.
        auto coins = vector<uint32_t>(no_coin_values);
        rep (c, no_coin_values) {
            cin >> coins[c];
        }

        auto change_matrix = vector<vector<uint32_t>>(no_coin_values + 1);
        rep(c, change_matrix.size()) change_matrix[c] = vector<uint32_t>(debt + 1);
        rep(c, debt + 1) change_matrix[0][c] = numeric_limits<uint32_t>::max();

        for (auto c = uint32_t{1}; c < no_coin_values + 1; ++c) {
            const auto coin = coins[c - 1];

            for (auto p = uint32_t{1}; p < change_matrix[c].size(); ++p) {
                if (coin == p) {
                    change_matrix[c][p] = 1;
                } else if (coin > p) {
                    const auto needed_pos = static_cast<uint32_t>(abs(static_cast<int32_t>(coin) - static_cast<int32_t>(p)));
                    change_matrix[c][p] = min(change_matrix[c - 1][p], min(1 + change_matrix[c][needed_pos], 1 + change_matrix[c - 1][needed_pos])); 
                } else {
                    change_matrix[c][p] = min(change_matrix[c - 1][p], min(1 + change_matrix[c][p - coin], 1 + change_matrix[c - 1][p - coin]));
                }
            }
        }

        const auto res = change_matrix[no_coin_values][debt];
        tsteps[i] = res;
    }

    rep(i, tsteps.size()) std::cout << tsteps[i] << endl;

    return 0;
}

