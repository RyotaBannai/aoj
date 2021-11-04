/*
支払い合計額、コインの枚数
各行にコインの価値
15 6
1 2 7 8 12 50

2
*/
#include <iostream>
#include <vector>
#define lps(i, j, n) for (int i = j; i < n; i++)
using namespace std;

static const int MMAX = 20;    // コインの数
static const int NMAX = 50000; // 求めたい金額の最大値
static const int INF = 1 << 29;

auto main() -> int
{
  int n, m;
  vector<int> c(MMAX + 1), t(NMAX + 1);

  cin >> n >> m;
  lps(i, 1, m + 1) cin >> c[i];
  t.assign(NMAX + 1, INF);

  t[0] = 0;
  /*
  二次元配列で全 j 円の場合を考慮してみるとわかりやすいが、
  1 <= i <= m のコインを使った時に考えうる j 円だけを考慮したほうが無駄がなく高速になる
  （0 <= j <= n の 1 区切りの範囲全てでななく、j + x（c[i]） のように i 番目の coin
  を加えたとき作ることができる合計の数値）
  よって、ネストされた内側の loop では、走査条件に j + x <= n を追加し、
  その成立する場合の数値 j（index）に対し、これまでの最適解 t[j + x] と、
  今回分のコインを引いた時の最適解（t[j]）に今回分のコイン足した（+1） `t[j] + 1`
  とを比較し、最小の方を新たな最適解として保持する
  */
  for (int x : c)
    for (int j = 0; j + x <= n; j++)
      t[j + x] = min(t[j + x], t[j] + 1);
  cout << t[n] << endl;

  return 0;
}
