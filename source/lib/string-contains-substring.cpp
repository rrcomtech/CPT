#include <vector>
#include <string>

#define uint        uint32_t
#define rep1(a, b)  for(uint a = 1; a < (b); ++a)

using namespace std;
using ll = long long;

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