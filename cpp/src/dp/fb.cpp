#include <iostream>
#include <vector>
#define lps(i, j, n) for (int i = j; i < n; i++)
using namespace std;

auto solve(int n) -> int
{
  int i;
  vector<int> f(50); // < 44
  f[0] = f[1] = 1;
  // i 番目の計算をする時点ですでに前の二つの値は計算済み
  lps(i, 2, n + 1) f[i] = f[i - 1] + f[i - 2];
  return f[n];
}

auto main() -> int
{
  int n;
  cin >> n;
  cout << solve(n) << endl;

  return 0;
}