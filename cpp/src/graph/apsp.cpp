#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;

int n;
static const int MAX = 100;
static const long long INF = 1LL << 32;
long long d[MAX][MAX];

void floyd()
{
  lp(k, n) lp(i, n)
  /* まず隣接していない頂点どうしの場合は、continue で処理をパス */
  {
    if (d[i][k] == INF)
      continue;
    lp(j, n)
    {
      if (d[k][j] == INF)
        continue;
      d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    }
  }
}

void solve()
{
  bool negative = false;
  // 負の閉路：
  // 通常は 0 が最小になるが、 k(=j) を経由した i->k c=-7, k->i c=5 のような場合に 0 以下になる
  lp(i, n) if (d[i][i] < 0) negative = true;
  if (negative)
    cout << "NEGATIVE CYCLE" << endl;
  else
    lp(i, n)
    {
      lp(j, n)
      {
        if (j)
          cout << " ";
        if (d[i][j] == INF)
          cout << "INF";
        else
          cout << d[i][j];
      }
      cout << endl;
    }
}

auto main() -> int
{
  int e, u, v, c;
  cin >> n >> e;

  lp(i, n) lp(j, n) d[i][j] = i == j ? 0 : INF;
  lp(i, e) cin >> u >> v >> c, d[u][v] = c;

  floyd();
  solve();

  return 0;
}