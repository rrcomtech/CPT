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

#include "math.h"


#define rep(a, b)   for(size_t a = 0; a < (b); ++a)
#define rep1(a, b)  for(size_t a = 1; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define endl        '\n'
#define cd(a)       static_cast<double>(a)
#define csize(a)     static_cast<size_t>(a)

using namespace std;
using ll = long long;
using ull = size_t;
using Graph = vector<vector<ll>>;
using uint = uint32_t;

bool compf(double x, double y, double epsilon = 0.001f){
  if(fabs(x - y) < epsilon)
    return true; //they are same
  return false; //they are not same
}

void solve() {
  ll x1,y1,x2,y2, r1,r2;
  cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

  if (x1 == x2 && y1 == y2) {
    if (r1 == r2) {
      if (r1 == 0) {
        cout << "1" << endl;
        return;
      }
      // 1
      cout << "oo" << endl;
      return;
    } else {
      // 2
      cout << "0" << endl;
      return;
    }
  }

  auto d2 = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
  auto r1r2p = (r1+r2)*(r1+r2);
  auto r1r2m = (r1-r2)*(r1-r2);

  // 3
  if (d2 > r1r2p) {
    cout << "0" << endl;
    return;
  }

  // 4
  if (d2 < r1r2m) {
    cout << "0" << endl;
    return;
  }

  // 5
  if (d2 == r1r2p) {
    cout << "1" << endl;
    return;
  }

  // 6
  if (d2 == r1r2m) {
    cout << "1" << endl;
    return;
  }

  // 7
  if (d2 < r1r2p) {
    cout << "2" << endl;
    return;
  }

  return;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);

  ull t;
  cin >> t;

  rep(i,t) solve();

  return 0;
}
