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
using ull = size_t;

struct Street {
  ull id;
  ull start;
  ull dest;
  ull length;
};

using namespace std;
using ll = long long;
using Graph = vector<vector<Street>>;
using uint = uint32_t;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);

  ull n, m;
  cin >> n >> m;

  auto graph = Graph(n+1);
  rep(i, m) {
    ull s, t, l;
    cin >> s >> t >> l;

    Street st{i+1, s, t, l};

    graph[s].push_back(st);
    graph[t].push_back(st);
  }

  auto q = queue<ull>();
  auto start = ull{1};
  auto costs = vector<ull>(n+1, SIZE_MAX);

  auto predecessor = vector<vector<Street>>(n+1);

  q.push(start);
  costs[start] = 0;

  // Djikstra
  while (!q.empty()) {
    auto node = q.front();
    q.pop();

    for (const auto& street : graph[node]) {
      const auto& dest = street.dest;
      const auto& length = street.length;

      if (costs[node] + length == costs[dest]) {
        predecessor[dest].push_back(Street{street.id, node});
      } else if (costs[node] + length < costs[dest]) {
        costs[dest] = costs[node] + length;
        predecessor[dest].clear();
        predecessor[dest].push_back(Street{street.id, node});
        q.emplace(dest);
      }
    }
  }

  // Calculate the essential streets.
  auto essential_streets = set<ull>();
  auto visited = vector<bool>(n+1, false);
  auto q2 = queue<ull>();
  q2.push(2);

  while (!q2.empty()) {
    const auto f = q2.front();
    q2.pop();

    for (const auto& p : predecessor[f]) {
      essential_streets.emplace(p.id);
      if (!visited[p.start]) {
        q2.emplace(p.start);
        visited[p.start] = true;
      }
    }
  }

  cout << essential_streets.size() << endl;
  for (auto itr = essential_streets.begin(); itr != essential_streets.end(); ++itr) {
    cout << *itr << " ";
  }
  cout << endl;

  return 0;
}
