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
#include <string>


#define rep(a, b)   for(uint a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define uint        uint32_t
#define endl        '\n'
#define cd(a)       static_cast<double>(a)

using namespace std;
using Graph = vector<vector<int>>;
using ll = long long;

bool resolve(string word, ll index, stack<char> patterns) {
    if (patterns.empty() && index != word.size()) return false;

    if (index == word.size()) {
        while (!patterns.empty()) {
            const auto top = patterns.top();
            if (top != '*') return false;
            patterns.pop();
        }
        return true;
    }

    const auto t = patterns.top();

    if (t != '*' && t != '+') {
        if (word[index] != t) return false;
        patterns.pop();
        return resolve(word, index + 1, patterns);
    } else {
        if (t == '*') {
            const auto res1 = resolve(word, index + 1, patterns);
            patterns.pop();
            const auto res2 = resolve(word, index, patterns);
            return res1 || res2;
        }
        if (t == '+') {
            patterns.pop();
            patterns.push('*');
            const auto res1 = resolve(word, index + 1, patterns);
            patterns.pop();
            const auto res2 = resolve(word, index + 1, patterns);
            return res1 || res2;
        }
    }
    // Should not appear
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    uint cases;
    cin >> cases;
    cin.ignore(100, '\n');

    rep(t, cases) {
        string pattern, text = "";
        std::getline(std::cin, pattern);
        std::getline(std::cin, text);

        reverse(all(pattern));
        auto patternStack = stack<char>();
        for (const auto& c : pattern) patternStack.push(c);

        if (resolve(text, 0, patternStack)) std::cout << "Yes" << endl;
        else std::cout << "No" << endl;
    }


    return 0;
}

