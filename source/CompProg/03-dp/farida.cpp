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

using namespace std;
using Graph = vector<vector<int>>;
using ll = long long;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    uint no_monsters;
    cin >> no_monsters;

    auto sum = ll{0};
    auto back = ll{0};

    rep (i, no_monsters) {
        uint coins;
        cin >> coins;

        auto temp_sum = back + coins;
        back = max(sum, back);
        sum = temp_sum;
    }

    const auto res = max(sum, back);

    std::cout << res << endl;
    return 0;
}

