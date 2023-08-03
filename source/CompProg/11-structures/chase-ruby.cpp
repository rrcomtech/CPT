#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n,m,k;
  cin >> n >> m >> k;
  vector<tuple<int,int,int>> edges(m);
  for (auto& [u, v, w] : edges)
    cin >> u >> v >> w, --u, --v;
  // Binary search for the first q that returns false.
  cout << *ranges::partition_point(views::iota(0,1e6+1), [&](int q) {
    vector dp(2*k-1, vector<int>(n, -1e9));
    fill(begin(dp[0]), end(dp[0]), 0);
    // dp[i][v] = Maximum count of edge with w >= q on a path to v with length i or negative if no such path exists
    for (int i = 1; i < 2*k-1; i++) {
      for (const auto& [u,v,w] : edges)
        dp[i][v] = max(dp[i][v], dp[i-1][u] + (w >= q));
      if (i >= k && *max_element(begin(dp[i]), end(dp[i])) > i / 2)
        return true;
    }
    return false;
  }) - 1;
}