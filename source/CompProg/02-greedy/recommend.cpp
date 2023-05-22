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
#define cf(a)       static_cast<float>(a)

using namespace std;
using Graph = vector<vector<int>>;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);
    uint no_probs, input;
    cin >> no_probs >> input;

    auto smallProbs = std::vector<uint>();
    auto largeProbs = std::vector<uint>();
    auto sum = double{0};
    rep (i, no_probs) {
        uint temp;
        cin >> temp;
        sum += cf(temp);
        if (temp < input) smallProbs.push_back(temp);
        else largeProbs.push_back(temp);
    }
    sort(all(smallProbs));

    auto i = uint{0};

    while (i < smallProbs.size() && sum / (no_probs - i) < input) {
        auto f = smallProbs[i];
        sum -= f;
        ++i;
    }

    const auto res = static_cast<uint>(no_probs - i);

    std::cout << res << endl;

    return 0;
}
