#include <iostream>
#define lp(i, n) for (int i = 0; i < n; i++)
#define lps(i, j, n) for (int i = j; i < n; i++)
using namespace std;

auto gcd(int a, int b) -> int { return b ? gcd(b, a % b) : a; }

auto gcd2(int a, int b) -> int
// ループによる最大公約数
{
  int r;
  if (a < b)
    swap(a, b); // b < a を保証

  while (b > 0) {
    r = a % b;
    a = b;
    b = r;
  }
  return a;
}

auto main() -> int
{
  int a, b;
  cin >> a >> b;
  cout << gcd2(a, b) << endl;
}