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

    uint no, size;
    cin >> no >> size;
    auto three = uint{0};
    auto two = uint{0};
    auto one = uint{0};

    rep (i, no) {
        uint temp;
        cin >> temp;
        switch (temp) {
            case 1:
                ++one;
                break;
            case 2:
                ++two;
                break;
            case 3:
                ++three;
                break;
        }
    }

    auto m = uint{0};
    for (auto th = uint{0}; th < three + 1; ++th) {
        const auto res = th * 3;
        if (res > size) break;

        // How much is left, after 3's are applied.
        const auto rest = size - res;
        // How many 2's are needed.
        const auto required_twos = static_cast<uint>(floor(rest / 2));
        // How many 2's we can actually provide.
        const auto rest_by_twos = min(two, required_twos) * 2;
        // How many 1's are needed to fill the whole rest.
        const auto requires_ones = rest - rest_by_twos;
        // What the actual result would be.
        const auto f = th * uint{3} + min(required_twos, two) * uint{2} + min(requires_ones, one);

        // Save the result and break, if perfect solution found.
        if (f <= size) m = max(f, m);
        if (m == size) break;
    }

    std::cout << m << endl;

    return 0;
}

