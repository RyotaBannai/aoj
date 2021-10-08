#include <array>
#include <iostream>
#include <string>
#define lps(i, j, n) for (int i = j; i < n; i++)
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;

const int MAX = 1000;
auto solve(string s1, string s2) -> int
{
  array<array<int, MAX + 1>, MAX + 1> mat{}; // 全要素を 0 で初期化
  int i, j;
  int m = s1.size();
  int n = s2.size();
  int maxl = 0;

  s1 = ' ' + s1; // 1 オリジンにするためダミーの空白を追加
  s2 = ' ' + s2;

  lps(i, 1, m + 1) lps(j, 1, n + 1)
  // 共通部分を一つ見つけたときに斜め左上の数値をベースに +1 する.
  // それ以外は同じ数値を引き継ぐ
  {
    mat[i][j] = s1[i] == s2[j] ? mat[i - 1][j - 1] + 1 : max(mat[i - 1][j], mat[i][j - 1]);
    maxl = max(maxl, mat[i][j]);
  }

  return maxl;
}

auto main() -> int
{
  string s1, s2;
  int i, n;
  cin >> n;
  lp(i, n)
  {
    cin >> s1 >> s2;
    cout << solve(s1, s2) << endl;
  }

  return 0;
}