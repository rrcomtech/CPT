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

#define repse(a,b,c) for (auto a = ll{b}; a < (c); ++a)

using namespace std;
using Graph = vector<vector<int>>;
using ll = long long;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    uint tests;
    cin >> tests;

    rep(t, tests) {
        auto debt = uint32_t{0};
        auto no_coin_values = uint{0};
        cin >> debt >> no_coin_values;

        // Are sorted by concept.
        auto coins = vector<uint32_t>(10, 0);
        rep (c, no_coin_values) {
            cin >> coins[c];
        }

        const auto start = ll{-50};
        const auto end = ll{50};

        auto m = static_cast<ll>(debt);

        repse(a, start, end) {
            repse(b, start, end) {
                repse(c, start, end) {
                    repse(d, start, end) {
                        repse(e, start, end) {
                            repse(f, start, end) {
                                repse(g, start, end) {
                                    repse(h, start, end) {
                                        repse(i, start, end) {
                                            repse(j, start, end) {
                                                const auto res = a * coins[0] + b * coins[1] + c * coins[2] + d * coins[3] + e * coins[4] + f * coins[5] + g * coins[6] + h * coins[7] + i * coins[8] + j * coins[9];
                                                if (res == debt) {
                                                    m = min(m, a + b + c + d + e + f + g + h + i + j);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }           
                }
            }
        }

        std::cout << m << endl;

    }

    return 0;
}

