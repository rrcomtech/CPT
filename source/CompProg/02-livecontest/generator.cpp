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

void solve() {
  ull border, sum;
  std::cin >> border >> sum;

  auto included = vector<bool>(sum, true);

  for (auto num = 1; num < border; ++num) {
    if (!included[num]) continue;

    auto s = 0;
    for (auto num2 = 1; num < border; ++num) {
      if (!included[num2]) continue;
    }
  }
}

int main() {
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.precision(10);

    ull cases;
    std::cin >> cases;
    rep(i,cases) solve()

    return 0;
}
