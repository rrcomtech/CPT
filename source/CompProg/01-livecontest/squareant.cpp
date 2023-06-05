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


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    uint32_t number_of_samples;
    cin >> number_of_samples;

    uint32_t n, w, h, w_count, h_count;
    rep(xxx, number_of_samples) {
        cin >> n >> w >> h;

        w_count = 1;
        h_count = 1;

        rep(i, n) {
            if (w_count * (w + 1) < h_count * (h + 1)) {
                ++w_count;
            } else {
                ++h_count;
            }
        }

        auto res = max(w_count * w, h_count * h);
        cout << res << endl;
    }

    return 0;
}


