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


struct Point {
  ull x, y;
};

bool compareX(Point a, Point b) {
  return a.x < b.x;
}

bool compareY(Point a, Point b) {
  return a.y < b.y;
}

ull distance(Point p1, Point p2) {
  return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

ull bruteForce(vector<Point>& points, ull start, ull end) {
  auto m = SIZE_MAX;

  for (auto i = start; i < end; ++i) {
    for (auto j = i + 1; j < end; ++j) {
      m = min(m, distance(points[i], points[j]));
    }
  }

  return m;
}

ull merge(vector<Point>& points, ull min_distance) {
  sort(all(points), compareY);

  for (auto i = ull{0}; i < points.size(); ++i) {
    for (auto j = ull{i+1}; j < points.size() && (points[j].y - points[i].y) < min_distance; ++j) {
      min_distance = min(min_distance, distance(points[i], points[j]));
    }
  }

  return min_distance;
}

ull closestPairHelper(vector<Point>& points, ull start, ull end) {
  // Check if division yielded small enough partition to bruteforce
  auto no_els = end - start;
  if (no_els <= 3) {
    return bruteForce(points, start, end);
  }

  // Divide further
  auto middle = start + (end - start) / 2;

  auto leftShortest = closestPairHelper(points, start, middle);
  auto rightShortest = closestPairHelper(points, middle, end);

  auto m = min(leftShortest, rightShortest);
  auto barrier_area = vector<Point>();
  for (auto i = start; i < end; ++i) {
    // If xdiff negative: left of middle, xdiff positive: right of middle
    auto xdiff = static_cast<ll>(points[i].x) - static_cast<ll>(points[middle].x);
    if ((xdiff >= 0 && xdiff < m) || (xdiff < 0 && xdiff * (-1) < m)) {
      barrier_area.push_back(points[i]);
    }

  }

  m = min(m, merge(barrier_area, m));

  return m;
}

ull closestPair(vector<Point>& points) {
  sort(all(points), compareX);
  return closestPairHelper(points, 0, points.size());
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);

  ull n;
  cin >> n;

  auto points = vector<Point>(n);
  rep (i,n) {
    ull x,y;
    cin >> x >> y;

    points[i] = Point{x,y};
  }

  const auto closest_distance = closestPair(points);

  cout << closest_distance << endl;

  return 0;
}
