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

  auto check = [&](int q) {
    vector dp(2*k - 1, vector<int>(n, -1e9));
    fill(begin(dp[0]), end(dp[0]), 0);
    for (int i = 1; i < 2*k - 1; i++) {
      for (const auto& [u,v,w] : edges)
        dp[i][v] = max(dp[i][v], dp[i-1][u] + (w >= q));
      if (i >= k && *max_element(begin(dp[i]), end(dp[i])) > i / 2)
        return true;
    }
    return false;
  };

  int lo = -1, hi = 1e6+1;

  while (hi - lo > 1) {
    int mid = (lo + hi) / 2;
    if (check(mid))
      lo = mid;
    else
      hi = mid;
  }
  cout << lo << '\n';

  return 0;
}