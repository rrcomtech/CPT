#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <map>
#include <unordered_map>
#include <unordered_set>
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

ll gcd(ll a, ll b){
  return !a ? b : gcd(b % a, a);
}

ll g(ll x, ll n) {
  return (x*x - 1) % n;
}

bool isPrime(ll number){

  if(number < 2) return false;
  if(number == 2) return true;
  if(number % 2 == 0) return false;
  for(auto i=ll{3}; (i*i)<=number; i+=2) {
    if(number % i == 0 ) return false;
  }
  return true;

}

ll pollardsrho(ll x, ll y, ll n) {
  auto d = ll{1};
  auto i = ll{1};
  auto k = ll{2};

  while (d == 1) {
    x = g(x,n); // g(x)
    y = g(g(y,n),n); // g(g(y))
    d = gcd(abs(x - y), n);

    if (d != 1 && d != n) return d;

    ++i;
    if (i == k) {
      y = x;
      k = k * 2;
    }
  }

  return 0; // Should not appear
}

void primefactors(ll n, unordered_set<ll>& res) {
  if (n == 1 || n == 0) return;

  if (n % 2 == 0) {
    res.insert(2);
    n = n / 2;
  }

  auto x = ll{2};
  auto y = ll{2};
  while (n != 1) {
    if (isPrime(n)) {
      res.insert(n);
      return;
    }

    const auto f = pollardsrho(x,y,n);

    if (f == 0) break;

    if (n % f == 0) res.insert(f);
    n = n / f;
  }
}

void primefactors_simple(ll n, unordered_set<ll>& res) {
  while (n % 2 == 0) {
    res.insert(2);
    n = n / 2;
  }
  for (auto i = ll{3}; i * i <= n; i += 2) {
    while (n % i == 0) {
      n = n / i;
      res.insert(i);
    }
  }
  if (n > 2) { // for primes larger than 2
    res.insert(n);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);

  ull no_medals;
  cin >> no_medals;

  auto medals = vector<ll>(no_medals);
  rep (i, no_medals) {
    cin >> medals[i];
  }

  sort(all(medals));

  auto m = ll{1};
  auto factors = vector<unordered_set<ll>>(no_medals);
  auto map = unordered_map<ll, ll>();
  for (auto i = size_t{0}; i < factors.size(); ++i) {
    if (medals[i] == 1 || medals[i] == 0) continue;

    primefactors_simple(medals[i], factors[i]);
    auto largestCount = ll{0};
    for (const auto& factor : factors[i]) {
      largestCount = max(largestCount, map[factor]);
    }

    for (const auto& factor : factors[i]) {
      map[factor] = largestCount + 1;
    }

    m = max(largestCount + 1, m);
  }

  cout << m << endl;
  return 0;
}
