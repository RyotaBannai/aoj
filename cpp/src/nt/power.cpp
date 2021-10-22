#include <cmath>
#include <iostream>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;
using ull = unsigned long long;

auto pow(ull x, ull n, ull M) -> ull
{
  ull res = 1;
  if (n > 0) {
    res = pow(x, n / 2, M);
    res = n % 2 == 0 ? (res * res) % M : (((res * res) % M) * x) % M;
  }
  return res;
}

auto main() -> int
{
  ull x, n, M = 1000000007;
  cin >> x >> n;
  cout << pow(x, n, M) << endl;
}