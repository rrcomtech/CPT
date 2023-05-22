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

using namespace std;
using Graph = vector<vector<int>>;
using ll = long long;

bool calc(vector<ll> nums, ll v) {
    if (nums.size() == 0 && v == 23) return true;
    else if (nums.size() == 0 && v != 23) return false;

    auto f = nums.front();
    nums.erase(nums.begin());
    return calc(nums, v + f) || calc(nums, v - f) || calc(nums, v * f);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    std::cout.precision(10);

    uint t;
    cin >> t;

    rep (j,t) {
        auto numbers = vector<ll>(5);
        rep (i, numbers.size()) cin >> numbers[i];
        sort(all(numbers));

        auto found = false;
        do {
            auto numbers_copy = numbers;
            auto f = numbers_copy.front();
            numbers_copy.erase(numbers_copy.begin());
            if (calc(numbers_copy, f)) {
                std::cout << "Possible" << endl;
                found = true;
                break;
            }
        } while (next_permutation(all(numbers)));

        if (!found) std::cout << "Impossible" << endl;
    }
    return 0;
}

