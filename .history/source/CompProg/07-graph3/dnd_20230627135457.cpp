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
  auto buckets = vector<vector<ull>>(longestPath);
  auto currBucket = vector<ull>(graph.size(), SIZE_MAX);
  buckets[0].push_back(start);
  currBucket[start] = ull{0};

  // Iterate over all buckets.
  for (auto b = ull{0}; b < buckets.size(); ++b) {

    // Iterate over each element in the bucket.
    const auto bucket = buckets[b];
    for (auto itr = bucket.begin(); itr != bucket.end(); ++itr) {
      const auto& currentNode = *itr;

      // Iterate over all neighbors of an element.
      for (const auto& [ dest, length ] : graph[currentNode]) {
        if (currBucket[dest] == SIZE_MAX) {
          buckets[b + length].push_back(dest);
          currBucket[dest] = b + length;
        } else if (currBucket[dest] > b + length) {
          const auto prevBucket = currBucket[dest];
          
          buckets[b + length].push_back(dest);
          currBucket[dest] = b + length;

          buckets[prevBucket].erase(find(all(buckets[prevBucket]), dest));
        }
      }
    }
  }
  
  if (currBucket[end] == SIZE_MAX) {
    cout << "BRIBE DM WITH FOOD" << endl;
  } else {
    cout << currBucket[end] << endl;
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
  auto longestPath = ull{0};
  rep(i, edges) {
    ull s, d;
    cin >> s >> d;
    const auto p1 = proficiency[s];
    const auto p2 = proficiency[d];
    const auto cost = static_cast<ull>(pow((p1.first - p2.first), 2) + pow((p1.second - p2.second), 2));
    graph[s].push_back(make_pair(d, cost));
    graph[d].push_back(make_pair(s, cost));

    longestEdge += cost;
  }

  ull queries;
  cin >> queries;
  rep(i, queries) {
    ull start, end;
    cin >> start >> end;
    solve(graph, start, end, longestEdge);
  }

  return 0;
}
