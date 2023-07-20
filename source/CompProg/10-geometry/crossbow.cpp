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
using ll = long long;
using ull = size_t;
using Graph = vector<vector<ll>>;
using uint = uint32_t;


double pointDistance(double x1, double y1, double x2, double y2) {
  return sqrt(pow(x2-x1, 2) + pow(y2-y1,2));
}

// (x1,y1): start
// (x2,y2): target
// (x3,y3): point to take the angle to start
double angle(double x1, double y1, double x2, double y2, double x3, double y3) {
  auto a = pointDistance(x1,y1,x2,y2);
  auto b = pointDistance(x1,y1,x3,y3);
  auto c = pointDistance(x2,y2,x3,y3);

  auto cosC = (pow(a,2)+pow(b,2)-pow(c,2)) / (2 * a * b);
  auto degrees = acos(cosC) * 180 / M_PI;
  return degrees;
}

double distance(double x1, double y1, double x2, double y2, double x0, double y0) {
  auto up = abs((x2-x1)*(y1-y0)-(x1-x0)*(y2-y1));
  auto bot = sqrt(pow(x2-x1,2)+pow(y2-y1,2));

  return up / bot;
}

bool isBeforeStartingPoint(double x, double y, double tx, double ty, double px, double py) {
  if (angle(x,y,tx,ty,px,py) > 90) {
    return true;
  }
  return false;
}

void solve() {
  double x, y, tx, ty;
  cin >> x >> y >> tx >> ty;

  ull no_balloons;
  cin >> no_balloons;

  auto hits = ull{0};

  rep(i, no_balloons) {
    float bx,by,r;
    cin >> bx >> by >> r;

    if (isBeforeStartingPoint(x,y,tx,ty,bx,by)) {
      if (pointDistance(x,y,bx,by) <= r) {
        ++hits;
      }
    } else {
      const auto d = distance(x,y,tx,ty,bx,by);
      if (d <= r) ++hits;
    }

  }

  cout << hits << endl;
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
