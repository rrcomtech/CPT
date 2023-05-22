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

struct Node  { 
    bool end = true;
    struct Node *left; // 0
    struct Node *right; // 1
}; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    struct Node* tree = new struct Node();
    tree->left = NULL;
    tree->right = NULL;

    ll nets;
    cin >> nets;

    rep (n, nets) {
        string net;
        cin >> net;
        
        auto lastNode = tree;
        rep(i, net.size()) {
            if (net[i] == '*') {
                lastNode->end = false;
            } else {
                struct Node* nextNode = new struct Node();
                if (net[i] == '0') {
                    if (lastNode->left) {
                        lastNode = lastNode->left;
                    } else {
                        lastNode->left = nextNode;
                        lastNode = nextNode;
                    }
                } else if (net[i] == '1') {
                    if (lastNode->right) {
                        lastNode = lastNode->right;
                    } else {
                        lastNode->right = nextNode;
                        lastNode = nextNode;
                    }
                }
            }
        }
    }

    ll no_ips;
    cin >> no_ips;
    rep (i, no_ips) {
        string ip;
        cin >> ip;

        auto lastNode = tree;
        auto done = false;
        for (const auto c : ip) {
            if (c == '0') {
                // Take left path if possible
                if (lastNode->left) {
                    lastNode = lastNode->left;
                } else if (lastNode->end) {
                    done = true;
                    std::cout << "No" << endl;
                    break;
                } else {
                    done = true;
                    std::cout << "Yes" << endl;
                    break;
                }
            } else if (c == '1') {
                // Take left path if possible
                if (lastNode->right) {
                    lastNode = lastNode->right;
                } else if (lastNode->end) {
                    done = true;
                    std::cout << "No" << endl;
                    break;
                } else {
                    done = true;
                    std::cout << "Yes" << endl;
                    break;
                }
            }
        }

        if (!done) {
            std::cout << "Yes" << endl;
        }
    }

    return 0;
}

