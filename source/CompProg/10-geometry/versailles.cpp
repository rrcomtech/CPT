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
  ll x;
  ll y;
};

ll orientation(Point& p1, Point& p2, Point& p3) {
  return (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);
}

ll distance(Point& p, Point& q) {
  // Function to compute the squared distance between two points
  auto dx = p.x - q.x;
  auto dy = p.y - q.y;
  return dx * dx + dy * dy;
}

ll next_point(std::vector<Point>& points, ll curr_point, vector<bool>& visited, ll start_point) {
  // Helper function to find the next point in the convex hull
  auto n = points.size();
  auto next_pt = (curr_point + 1) % n;
  while (visited[next_pt]) next_pt = (next_pt + 1) % n;

  for (auto i = ull{0}; i < n; ++i) {
    if (i == curr_point || i == next_pt || visited[i]) continue;

    const auto o = orientation(points[curr_point], points[next_pt], points[i]);

    if (o < 0) {
      next_pt = i;
    } else if (o == 0) {

      if (i != start_point) {
        if (next_pt == start_point) {
          next_pt = i;
        } else {
          // Neither i nor next_pt are the starting point. Choose the one closer to curr_point
          auto dist_i = distance(points[curr_point], points[i]);
          auto dist_next = distance(points[curr_point], points[next_pt]);

          if (dist_i < dist_next) {
            next_pt = i;
          }
        }
      }
    }
  }
  return next_pt;
}

std::vector<Point> jarvis_march(std::vector<Point>& points, vector<bool>& visited) {
  // Main function to compute the convex hull of a set of 2D points using Jarvis march algorithm
  auto n = points.size();
  if (n <= 3) return points;

  // Find the leftmost point as the starting point
  auto start_point = ll{0};
  for (auto i = ll{1}; i < n; ++i) {
    if (visited[i]) continue;

    if ((points[i].y < points[start_point].y || (points[i].y == points[start_point].y && points[i].x < points[start_point].x)) || visited[start_point]) {
      start_point = i;
    }
  }

  // Initialize the convex hull with the starting point
  auto convex_hull = vector<Point>{points[start_point]};

  // Find the remaining points of the convex hull
  auto next_pt = ll{start_point};
  do {
    next_pt = next_point(points, next_pt, visited, start_point);
    convex_hull.push_back(points[static_cast<unsigned long>(next_pt)]);
    visited[next_pt] = true;
  } while (next_pt != start_point);

  convex_hull.pop_back(); // Starting point is pushed twice. Remove second occurrence of starting point

  return convex_hull;
}

void solve() {
  ull no_els;
  cin >> no_els;

  auto points = vector<Point>(no_els);
  rep(i, no_els) {
    ll x,y;
    cin >> x >> y;
    points[i] = Point{x,y};
  }

  auto visited_elements = vector<bool>(no_els, false);
  auto hull_elements = ull{0};
  auto layers = ull{0};

  while (hull_elements < points.size()) {
    auto convex_hull = jarvis_march(points, visited_elements);
    hull_elements += convex_hull.size();
    ++layers;
  }

  cout << layers << endl;
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
