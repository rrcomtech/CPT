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
using Graph = vector<vector<int>>;
using ll = long long;
using uint = uint32_t;

ll findLargestFunFactor(ll n, const vector<ll>& funFactors, const vector<vector<ll>>& directBosses) {
    vector<vector<ll>> dp(n+1, vector<ll>(2, 0));

    function<void(ll)> dfs = [&](ll boss) {
        if (directBosses[boss].empty()) {
            dp[boss][0] = funFactors[boss];
            return;
        }

        ll bossComing       = funFactors[boss];
        ll bossNotComing    = 0;

        for (const auto& employee : directBosses[boss]) {
            dfs(employee);
            bossNotComing   += max(dp[employee][0], dp[employee][1]);
            bossComing      += dp[employee][1];
        }

        dp[boss][0] = bossComing;
        dp[boss][1] = bossNotComing;
    };

    dfs(1);

    return max(dp[1][0], dp[1][1]);
}

int main() {
    ll n;
    cin >> n;

    vector<ll> funFactors(n+1);
    for (ll i = 1; i <= n; i++) {
        cin >> funFactors[i];
    }

    vector<vector<ll>> directBosses(n+1);
    for (ll i = 2; i <= n; i++) {
        ll boss;
        cin >> boss;
        directBosses[boss].push_back(i);
    }

    ll largestFunFactor = findLargestFunFactor(n, funFactors, directBosses);
    cout << largestFunFactor << endl;

    return 0;
}