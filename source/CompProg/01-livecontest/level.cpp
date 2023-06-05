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


#define rep(a, b)   for(size_t a = 0; a < (b); ++a)
#define rep1(a, b)  for(size_t a = 1; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define endl        '\n'
#define cd(a)       static_cast<double>(a)
#define csize(a)     static_cast<size_t>(a)

using namespace std;
using Graph = vector<vector<int>>;
using ll = long long;
using uint = uint32_t;

struct Trap {
    ll x;
    ll y;
};

ll numberPaths(ll i, ll j, bool wasTrap, vector<Trap> traps) {
    if (i == 1 || j == 1) {
        if (wasTrap) return 1;
        else return 0;
    }

    bool trapped = false;
    rep (k, traps.size()) {
        if (traps[k].x == i && traps[k].y == j) trapped =true;
    }

    return numberPaths(i - 1, j, trapped, traps)+ numberPaths(i, j - 1, trapped, traps);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    ll width, height;
    cin >> width >> height;
    auto rows = vector<string>(height);
    auto traps = vector<Trap>();
    rep(k, height) {
        cin >> rows[k];
        rep (i, rows[k].size()) {
            if (rows[k][i] == '*') {
                Trap t;
                t.y = i;
                t.x = k;
                traps.push_back(t);
            }
        }
    }

    auto tempVec = vector<ll>(width);
    auto dp = vector<vector<ll>>(height, tempVec);

    std::cout << numberPaths(4,4,false,traps) << endl;

    return 0;
}
