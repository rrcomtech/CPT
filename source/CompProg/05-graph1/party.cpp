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

struct Tree {
    ll number;
    ll boss;
    ll fun;
    vector<Tree*> subtrees;
    bool boss_coming = true;
};

ll subtree_weight(Tree* subtree) {
    if (subtree->subtrees.size() == 0) return subtree->fun;

    auto child_weight = accumulate(all(subtree->subtrees), [](Tree a, Tree b) {
        return subtree_weight(a) + subtree_weight(b);
    });

    return max
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    ll colleagues;
    cin >> colleagues;

    auto fun = vector<ll>(colleagues);
    rep (i, csize(colleagues)) {
        cin >> fun[i];
    }

    auto subtrees = vector<Tree>();
    subtrees.push_back(Tree{0, 0, fun[0]});
    rep (i, csize(colleagues - 1)) {
        ll boss;
        cin >> boss;

        auto t = Tree{static_cast<ll>(i+1), boss - 1, fun[i+1]};
        subtrees.push_back(t);    
    }

    rep1 (i, subtrees.size()) {
        subtrees[subtrees[i].boss].subtrees.push_back(&subtrees[i]);
    }

    // Complete tree.
    auto tree = subtrees[0];



    return 0;
}
