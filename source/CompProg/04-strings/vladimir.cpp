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

using namespace std;
using Graph = vector<vector<int>>;
using ll = long long;

vector<ll> prefix(string word) {
    const auto n = word.size();
    auto P = vector<ll>(n, 0);

    rep1(i, n) {
        auto j = static_cast<size_t>(P[i-1]);
        while (j > 0 && word[i] != word[j]) {
            j = static_cast<size_t>(P[j - 1]);
        }
        if (word[i] == word[j]) {
            j = j+1;
        }
        P[i] = static_cast<ll>(j);
    }

    return P;
}

// As in lecture
bool contains(string word, string substring) {
    const auto size = substring.size();
    const auto P = prefix(substring.append("#").append(word));

    for (const auto& num : P) {
        if (static_cast<size_t>(num) == size) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    ll noBlocks, highestColorCode;
    cin >> noBlocks >> highestColorCode;

    auto blocks = string("");
    rep (i, noBlocks) {
        string temp;
        cin >> temp;
        if (stoi(temp) <= highestColorCode) blocks.append(temp);
    }

    auto originalBlocks = blocks;

    auto results = vector<ll>();
    results.push_back(noBlocks);
    
    auto realPointer = static_cast<ll>(blocks.size() - 2);
    auto mirror = blocks;
    reverse(all(mirror));
    auto mirrorPointer = 0;

    auto prefix = string("");
    auto removedElements = string("");
    for (auto currCount = noBlocks - 1; currCount >= noBlocks / 2; --currCount) {
        removedElements += mirror[mirrorPointer];
        ++mirrorPointer;

        if (prefix.size() > 0) prefix.erase(prefix.begin() + prefix.size() - 1);    
        auto prefixSpace = removedElements.size() - prefix.size();
        while (prefixSpace > 0 && realPointer >= 0) {
            prefix = blocks[static_cast<size_t>(realPointer)] + prefix;

            --prefixSpace;
            if (realPointer == 0) break;
            --realPointer;
        }

        if (prefixSpace > 0) break; // Something went wrong.
        if (prefix == removedElements) results.push_back(currCount);
    }

    sort(all(results));

    rep (i, results.size()) {
        std::cout << results[i] << " ";
    }

    std::cout << endl;

    return 0;
}