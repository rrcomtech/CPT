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
// Node: Set of Edges of (dest, length)
using Graph = vector<vector<pair<ull,ull>>>;
using uint = uint32_t;

void solve(Graph graph, ull start, ull end, ull longestPath) {
  auto dist = unordered_map<ull,ull>();
  for (auto i = ull{0}; i < graph.size(); ++i) {
    dist[i] = SIZE_MAX;
  }
  dist[start] = ull{0};
  auto q = priority_queue<pair<ull,ull>>();
  q.push({0,start});

  auto processed = vector<bool>(graph.size(), false);
  while (!q.empty()) {
    const auto f = q.top().second;
    q.pop();

    if (processed[f]) continue;
    processed[f] = true;

    for (auto& [ dest, length ] : graph[f]) {
      if (dist[f] + length < dist[dest]) {
        dist[dest] = dist[f] + length;
        q.push({(-1) * dist[dest], dest});
      }
    }
  }

  if (dist[end] == SIZE_MAX) {
    cout << "BRIBE DM WITH FOOD" << endl;
  } else {
    cout << dist[end] << endl;
  }  
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);

  ull nodes,edges;
  cin >> nodes;

  auto proficiency = vector<pair<ll,ll>>(nodes+1);
  rep1(i, nodes+1) {
    ll s1,s2;
    cin >> s1 >> s2;
    proficiency[i] = make_pair(s1,s2);
  }

  cin >> edges;

  auto graph = Graph(nodes+1);
  
  rep(i, edges) {
    ull s, d;
    cin >> s >> d;
    const auto p1 = proficiency[s];
    const auto p2 = proficiency[d];
    const auto cost = static_cast<ull>(pow((p1.first - p2.first), 2) + pow((p1.second - p2.second), 2));
    graph[s].push_back(make_pair(d, cost));
    graph[d].push_back(make_pair(s, cost));
  }

  cout << longestPath << endl;
  return 0;

  ull queries;
  cin >> queries;
  rep(i, queries) {
    ull start, end;
    cin >> start >> end;
    solve(graph, start, end, longestPath);
  }

  return 0;
}
