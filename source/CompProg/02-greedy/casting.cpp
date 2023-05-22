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
#define reps(a,b,c) for(uint a = c; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define uint        uint32_t
#define endl        '\n'

using namespace std;
using Graph = vector<vector<int>>;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    uint t;
    cin >> t;

    rep (j, t) {
        uint no_blocks;
        string blocks;
        cin >> no_blocks;
        cin >> blocks;

        auto target_black = false;
        auto black_pos = std::vector<uint>();
        auto white_pos = std::vector<uint>();
        rep (i, blocks.size()) {
            if (blocks[i] == 'B') black_pos.push_back(i);
            else white_pos.push_back(i);
        }
        // Determine whether finding a solution is possible: |B| is even or |W| is even. 
        if ((black_pos.size()) % 2 == 0 || (blocks.size() - black_pos.size()) % 2 == 0) {
            if (black_pos.size() % 2 == 0 && white_pos.size() % 2 == 0) target_black = black_pos.size() < white_pos.size();
            else if (black_pos.size() % 2 == 0) target_black = true;
            std::cout << "YES" << endl;
        } else {
            std::cout << "NO" << endl;
            continue;
        }

        auto swaps = vector<uint>();
        if (target_black) {
            for (auto i = uint{0}; i < black_pos.size(); i = i + 2) {
                for (auto pos = black_pos[i]; pos < black_pos[i+1]; ++pos) swaps.push_back(pos + 1);
            }
        } else {
            for (auto i = uint{0}; i < white_pos.size(); i = i + 2) {
                for (auto pos = white_pos[i]; pos < white_pos[i+1]; ++pos) swaps.push_back(pos + 1);
            }
        }

        std::cout << swaps.size() << endl;
        rep (i, swaps.size()) std::cout << swaps[i] << " ";
        std::cout << endl;
    }

    return 0;
}

