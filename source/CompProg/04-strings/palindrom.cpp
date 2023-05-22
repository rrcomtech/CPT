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

    string word;
    getline(cin, word);

    auto leastChanges = cd(word.size()) / 2;

    auto n = word.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        dp[i][i] = 0;
    }

    for (int l = 2; l <= n; ++l) {
        for (int i = 0; i < n - l + 1; ++i) {
            int j = i + l - 1;
            if (word[i] == word[j]) {
                dp[i][j] = dp[i + 1][j - 1];
            } else {
                dp[i][j] = std::min(dp[i + 1][j] + 1, min(dp[i][j - 1] + 1, dp[i + 1][j - 1] + 1));
            }
        }
    }

    const auto res = dp[0][n-1];
    std::cout << res << endl;

    return 0;
}
