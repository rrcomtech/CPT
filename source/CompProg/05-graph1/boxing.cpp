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
#include <cstring>


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

// Syntax: Pair of (Moving up, Moving right)
const auto knight_moves = vector<pair<ll,ll>>{
    pair(-1, 2), pair(1, 2), // Right
    pair(2, 1), pair(2, -1), // Up
    pair(-1, -2), pair(1, -2), // Left
    pair(-2, -1), pair(-2, 1) // Down
};

bool in_bounds(ll w, ll h, pair<ll,ll> field) {
    return field.first < h && field.first >= 0 && field.second < w && field.second >= 0;
}

pair<pair<ll,ll>, vector<vector<pair<ll,ll>>>> bfs(vector<vector<vector<pair<size_t,size_t>>>>& adjacent_matrix, pair<size_t,size_t> start, vector<string> board, ll w, ll h) {
    auto q = queue<pair<size_t,size_t>>();
    auto v_empty = vector<pair<size_t,size_t>>();
    auto column_seen = vector<pair<ll,ll>>(adjacent_matrix[0].size(), pair<ll,ll>(-1,-1));
    auto seen = vector<vector<pair<ll,ll>>>(adjacent_matrix.size(), column_seen);
    q.push(start);
    
    while (!q.empty()) {
        auto node = q.front();
        q.pop();

        for (const auto& move : knight_moves) {
            auto child = node;
            child.first += move.first;
            child.second += move.second;

            if (in_bounds(w, h, child) && seen[child.first][child.second] == pair<ll,ll>(-1,-1)
                    && (!isupper(board[child.first][child.second]) || board[child.first][child.second] == 'N')) {
                // Set previous node of current node.
                seen[child.first][child.second] = node;

                if (board[child.first][child.second] == 'N') {
                    return pair<pair<ll,ll>, vector<vector<pair<ll,ll>>>>(child, seen);
                }
                
                q.push(child);
            }
        }
    }
    return pair<pair<ll,ll>, vector<vector<pair<ll,ll>>>>(pair<ll,ll>(-1,-1), vector<vector<pair<ll,ll>>>{});
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    ll w, h;
    cin >> w >> h;

    // Each field holds the list of fields, that is "surrounded" by 
    // (aka that a knight can reach).
    auto temp_row = vector<vector<pair<size_t, size_t>>>(w);
    auto adjacence_matrix = vector<vector<vector<pair<size_t,size_t>>>>(h, temp_row);

    auto board = vector<string>(csize(h));
    auto king_position = pair<ll,ll>();
    rep (i, csize(h)) {
        string t;
        cin >> t;

        rep(j, csize(w)) {
            if (t[j] == 'k') king_position = pair(h - i - 1, j);
        }

        board[h - i - 1] = t;
    }

    const auto actual_moves = bfs(adjacence_matrix, king_position, board, w, h);
    auto target = actual_moves.first;
    const auto matrix = actual_moves.second;

    auto last = target;

    auto o = string("");

    if (target == pair<ll,ll>(-1,-1)) {
        std::cout << "Resign" << endl;
    } else {
        auto ci = size_t{0};
        while (last != king_position) {
            const auto last_pred = matrix[last.first][last.second];
            o +=    to_string(last.first+1) + " " +
                    to_string(last.second+1) + " " +
                    to_string(last_pred.first+1) + " " +
                    to_string(last_pred.second+1) + " " + endl;
            last = last_pred;
            ++ci;
        }

        cout << "Checkmate in " << ci << endl;
        cout << o;
    }

    return 0;
}
