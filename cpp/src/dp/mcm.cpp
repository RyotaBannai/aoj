#include <array>
#include <iostream>
#define lp(i, n) for (int i = 0; i < n; i++)
#define lps(i, j, n) for (int i = j; i < n; i++)
using namespace std;

static const int N = 100;

auto main() -> int
{
  int i, l, k, n;
  array<int, N + 1> p{};
  array<array<int, N + 1>, N + 1> mat{}; // Mi Mj の最小計算コストを保管
  cin >> n;

  // p[n+1] := Mi が p[i-1]　x　p[i] の行列となるような`1次元配列`
  // pi には行列の縦横の size を格納（i.g. p2 は`M3 の row の大きさ`と等しい）
  lps(i, 1, n + 1) cin >> p[i - 1] >> p[i];
  lps(l, 2, n + 1) lps(i, 1, n - l + 2)
  // n 個の行列を l ごとに区切り最小の計算を求めていく.
  // i ~ j の区間を広げていき、その間の最小値の計算は前の loop で計算済みなのでその結果をもとに k
  // 分ずらしながら各回の最小を求める.
  // 計算は結局は (M1 min cost) + (M2 min cost) + (M1 と M2 の積の cost) であり、それを k
  // をずらしながら min を求める
  {
    int j = i + l - 1;
    // cout << i << " " << j << endl; // for better understandings.
    mat[i][j] = 1 << 21;
    lps(k, i, j) mat[i][j] = min(mat[i][j], mat[i][k] + mat[k + 1][j] + p[i - 1] * p[k] * p[j]);
  }

  cout << mat[1][n] << endl;
  return 0;
}