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

ll fac(ll n) {
    if (n == 1 || n == 0) return 1;
    return n*fac(n-1);
}

ll over(ll up, ll low) {
    return cd(fac(up)) / cd(fac(up - low) * fac(low));
}

uint f(ll n, ll p) {
    if (n == 0 || p == 0) return 0;
    if (n == p) return 1;
    if (p == 1) return 1;

    const auto mod = uint{998244353};
    auto res = ll{0};

    if (p == 2) {
        for (auto i = uint{1}; i <= n - 1; ++i) {
            res += over(n, i) - 1;
        }
    } else {
        for (auto i = uint{1}; i <= n - (p - 1); ++i) {
            const auto o = over(n, i);
            res += cd(o * f(n - i, p - 1)) / 2;
        }
    }

    return res % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    uint cases;
    cin >> cases;
    rep (t, cases) {
        uint n, p;
        cin >> n >> p;

        const auto res = f(n, p);

        std::cout << res << endl;
    }

    return 0;
}

