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
#include <cstdint>


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
  __int128 s = (__int128) x * (__int128) x;
  return (s + (__int128) 1) % n;
}

bool isPrime(ll number){

  if(number < 2) return false;
  if(number == 2) return true;
  if(number % 2 == 0) return false;
  for(auto i=ll{3}; (i*i)<=number; i+=2){
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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);

  auto largestFactor = ll{1};
  ll n;
  cin >> n;

  if (n % 2 == 0) {
    largestFactor = 2;
    n = n / 2;
  }

  auto x = ll{2};
  auto y = ll{2};
  while (n != 1) {
    if (isPrime(n)) {
      largestFactor = max(largestFactor, n);
      break;
    }

    const auto f = pollardsrho(x,y,n);

    if (f == 0) break;

    largestFactor = max(f, largestFactor);
    n = n / f;
  }

  cout << largestFactor << endl;

  return 0;
}
