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

vector<ll> z(string word) {
    const auto n = word.size();
    auto Z = vector<ll>(n, 0);

    auto l = ll{0};
    auto r = ll{0};

    rep1(i, n) {
        if (i < r) {
            Z[i] = min(r - i + 1, Z[static_cast<size_t>(i - l)]);
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

    ll periodicalNumbers;
    cin >> periodicalNumbers;
    ll includedNumbers;
    cin >> includedNumbers;

    string word;
    string substring;
    rep(i, periodicalNumbers) {
        uint temp;
        cin >> temp;
        word.append(to_string(temp));
    }
    rep(i, includedNumbers) {
        uint temp;
        cin >> temp;
        substring.append(to_string(temp));
    }

    if (substring.size() > word.size()) {
        std::swap(word, substring);
    }

    const auto P = prefix(substring + "#" + word + word);
    rep(i, P.size()) {
        const auto curr = P[i];

        // With prefix function, this is the way to test if a substring is contained.
        if (curr == static_cast<ll>(substring.size())) {
            auto wordIndex = size_t{(i - substring.size()) % word.size()};
            auto substringIndex = size_t{0};

            while (wordIndex != (i - substring.size() - 1) % word.size()) {
                if (word[wordIndex] != substring[substringIndex]) {
                    std::cout << "NO" << endl;
                    return 0;
                }

                ++wordIndex;
                ++substringIndex;
                wordIndex = wordIndex % word.size();
                substringIndex = substringIndex % substring.size();
            }

            std::cout << "YES" << endl;
            return 0;
        }
    }

    // We did not break prior to this.
    std::cout << "NO" << endl;

    return 0;
}

