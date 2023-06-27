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
using Graph = vector<vector<pair<ll, double>>>;
using uint = uint32_t;

double dist(pair<ll, ll> pos1, pair<ll, ll> pos2) {
  return sqrt(pow(pos1.first - pos2.first, 2) + pow(pos1.second - pos2.second, 2));
}

bool isConnected(Graph& graph) {
  auto q = queue<ll>();
  auto visited = vector<bool>(graph.size(), false);
  q.push(0);
  visited[0] = true;

  while (!q.empty()) {
      auto current = q.front();
      q.pop();
      for (const auto& [a, b] : graph[current]) {
          if (!visited[a]) {
              visited[a] = true;
              q.push(a);
          }
      }
  }

  for (auto v : visited) if (!v) return false;
  return true;
}

pair<ll, double> modified_dijkstra(Graph& graph, int start) {
  auto distance = vector<double>(graph.size(), numeric_limits<double>::max());
  auto visited = vector<bool>(graph.size(), false);
  auto q = priority_queue<pair<double, ll>, vector<pair<double, ll>>, greater<pair<double, ll>>>();
  
  q.push({0, start});
  distance[start] = 0;

  while (!q.empty()) {
      auto [current_distance, current_index] = q.top();
      q.pop();
      if (visited[current_index]) {
          continue;
      }
      visited[current_index] = true;
      for (auto [a, b] : graph[current_index]) {
          if (distance[a] > distance[current_index] + b) {
              distance[a] = distance[current_index] + b;
              q.push({distance[a], a});
          }
      }
  }

  double max_distance = 0;
  int max_index = 0;
  rep(i, distance.size()) {
      if (distance[i] > max_distance) {
          max_distance = distance[i];
          max_index = i;
      }
  }

  return {max_index, max_distance};
}

void solve() {
  ull no_cities;
  cin >> no_cities;

  // Number of cities without duplicated cities.
  auto actual_cities = ll{0};

  auto surroundings = vector<pair<ll,ll>>();
  for (auto dx = ll{-10}; dx < ll{10}; ++dx) {
    for (auto dy = ll{-10}; dy < ll{-10}; ++dy) {
      const auto pos = make_pair(dx, dy);
      if (dist(make_pair(ll{0}, ll{0}), pos) <= 10) {
        surroundings.push_back(pos);
      }
    }
  }

  auto cities = vector<pair<ll,ll>>();
  auto map = vector<vector<ll>>(1024, vector<ll>(1024, -1));
  rep (_, no_cities) {
    ll x,y;
    cin >> x >> y;

    if (map[x][y] == -1) {
      // ID for each city
      map[x][y] = actual_cities;
      cities.push_back({x, y});
      ++actual_cities;
    }
  }

  const auto in_bounds = [](ll x, ll y) {
    return x >= 0 && x < 1024 && y >= 0 && y < 1024;
  };

  auto graph = Graph(actual_cities);
  rep (i, actual_cities) {
    auto& [x, y] = cities[i];
    for (const auto& [ dx, dy ] : surroundings) {
      const auto surr_x = x + dx;
      const auto surr_y = y + dy; 
      if (in_bounds(surr_x, surr_y)) {
        const auto ind = map[surr_x][surr_y];
        if (ind != -1 && ind != i) {
          auto d = dist(cities[i], cities[ind]);
          graph[i].push_back({ind, d});
        }
      }
    }
  }

  if (!isConnected(graph)) {
    cout << "Send Kurdy" << endl;
  } else {

  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);

  ull cases;
  cin >> cases;
  rep (_, cases) solve();

  return 0;
}
