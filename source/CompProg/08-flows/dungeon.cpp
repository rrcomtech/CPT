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
using namespace std;
using ll = long long;

struct Node {
  ull x;
  ull y;
  ull capacity = 1;
  ull flow = 0;
};

using Graph = vector<vector<Node>>;
// Each cell holding a number of edges to other cells
using EdgeGraph = vector<vector<vector<pair<ull,ull>>>>;
using uint = uint32_t;

auto ops = vector<pair<ull,ull>>{
  make_pair(+1,0),
  make_pair(-1,0),
  make_pair(0,+1),
  make_pair(0,-1)
};

ull bfs(Graph& graph, EdgeGraph& edge_graph) {
  auto q = queue<pair<ull,ull>>();
  auto pred = vector<vector<Node*>>(graph.size(), vector<Node*>(graph[0].size(), nullptr));
  q.emplace(0,0);

  while (!q.empty()) {
    auto u = q.front();
    q.pop();

    if (u.first == graph.size()-1 && u.second == graph[0].size()-1) break;

    for (auto& n : edge_graph[u.first][u.second]) {
      const auto x = n.first;
      const auto y = n.second;
      if (pred[x][y] == nullptr && graph[x][y].capacity > graph[x][y].flow) {
        pred[x][y] = &(graph[x][y]);
        q.push(u);
      }
    }
  }

  auto flow = ull{0};
  if (pred[graph.size() - 1][graph[0].size() - 1] != nullptr) {
    // Augmenting path found
    flow = SIZE_MAX;

    for (auto p = pred[graph.size()-1][graph[0].size()-1]; p != nullptr; p = pred[p->x][p->y]) {
      p->flow = 1;
      revEdge.flow = revEdge.flow - 1;
    }
  }

  return flow;
}

ull fordfulkerson(Graph& graph, EdgeGraph& edge_graph) {


  return total_flow;
}

void solve() {
  ull w,h,p;
  cin >> w >> h >> p;

  auto positions = vector<pair<ull,ull>>(p);

  auto graph = Graph(w+2, vector<Node>(h+2));
  graph[w][h].capacity = SIZE_MAX;
  auto edge_graph = EdgeGraph(w+2,vector<vector<pair<ull,ull>>>(h+2));

  rep(i, p) {
    ull x,y;
    cin >> x >> y;
    positions[i] = make_pair(x,y);
    edge_graph[0][0].emplace_back(x,y);
  }

  rep1(x,w+1) {
    rep1(y,h+1) {
      graph[x][y].x = x;
      graph[x][y].y = y;

      for (const auto& move : ops) {
        edge_graph[x][y].emplace_back(x+move.first, y+move.second);
      }
    }
  }

  rep1(x, w+1) {
    edge_graph[x][0].emplace_back(w+1,h+1);
    edge_graph[x][h+1].emplace_back(w+1,h+1);
  }
  rep1(y, h+1) {
    edge_graph[0][y].emplace_back(w+1,h+1);
    edge_graph[w+1][y].emplace_back(w+1,h+1);
  }

  if (fordfulkerson(graph, edge_graph) == p) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);

  ull s;
  cin >> s;

  rep(_, s) solve();

  return 0;
}
