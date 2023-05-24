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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    ll noBlocks, highestColorCode;
    cin >> noBlocks >> highestColorCode;

    auto blocks = vector<ll>();
    rep (i, noBlocks) {
        ll temp;
        cin >> temp;
        if (temp <= highestColorCode) blocks.push_back(temp);
    }

    auto results = vector<ll>{static_cast<ll>(blocks.size())};

    auto testMatrix = vector<vector<bool>>();

    auto mirrored = blocks;
    mirrored.erase(mirrored.begin(), mirrored.begin() + 2);
    auto beforeMirror = vector<ll>{blocks[0]};
    auto afterMirror = vector<ll>{blocks[1]};

    for (auto pos = size_t{1}; pos <= csize(cd(blocks.size()) / 2); ++pos) {
        if (beforeMirror == afterMirror)
            results.push_back(static_cast<ll>(blocks.size() - pos));
        
        beforeMirror.insert(beforeMirror.begin(), afterMirror.at(0));
        afterMirror.erase(afterMirror.begin());

        while (beforeMirror.size() > afterMirror.size() && mirrored.size() > 0) {
            afterMirror.push_back(mirrored.at(0));
            mirrored.erase(mirrored.begin());
        }

    }

    // Results are added from largest to lowest.
    reverse(all(results));
    for (const auto& res : results) std::cout << res << " ";
    std::cout << endl;

    return 0;
}