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
#define rep1(a, b)  for(uint a = 1; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define uint        uint32_t
#define endl        '\n'
#define cd(a)       static_cast<double>(a)
#define csize(a)     static_cast<size_t>(a)

using namespace std;
using Graph = vector<vector<int>>;
using ll = long long;

// Not used here, but could also be used instead of the prefix function.
vector<ll> z(vector<ll> word) {
    const auto n = word.size();
    auto Z = vector<ll>(n, 0);

    auto l = ll{0};
    auto r = ll{0};

    Z[0] = n;
    for (auto i = size_t{1}; i < n; ++i) {
        if (i <= r) {
            Z[i] = min(static_cast<ll>(r - i + 1), Z[static_cast<size_t>(i - l)]);
        }
        while (static_cast<size_t>(i + Z[i]) < n && word[static_cast<size_t>(Z[i])] == word[static_cast<size_t>(i + Z[i])]) {
            Z[i] = Z[i] + 1;
        }

        if (i + Z[i] - 1 > r) {
            l = i;
            r = i + Z[i] - 1;
        }
    }

    return Z;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    ll noBlocks, highestColorCode;
    cin >> noBlocks >> highestColorCode;

    auto blocks = vector<ll>(noBlocks);
    rep (i, noBlocks) {
        cin >> blocks[i];
    }

    auto results = vector<ll>();
    results.push_back(blocks.size());

    auto blocksCopy = blocks;
    blocksCopy.push_back(highestColorCode + 1);
    auto blocksReverse = blocks;
    reverse(all(blocksReverse));
    for (const auto& b : blocksReverse) {
        blocksCopy.push_back(b);
    }

    auto Z = z(blocksCopy);

    rep1 (i, (cd(blocks.size()) / 2) + 1) {
        const auto reqIndex = blocksCopy.size() - (2 * i);
        if (Z.at(reqIndex) >= i) {
            const auto res = blocks.size() - i;
            results.push_back(res);
        }
    }

    sort(all(results));
    rep (i, results.size()) std::cout << results[i] << " ";
    std::cout << endl;

    return 0;
}