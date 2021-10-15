#include <algorithm>
#include <iostream>
#define lp(i, n) for (int i = 0; i < n; i++)
// #define fills(a, val) fill(begin(a), (begin(a) + N), val);
using namespace std;

enum class Color { White, Grey, Black };
static const int N = 100;
static const int INF = 1 << 21, NOT_CONNECTED = INF;
int n, mat[N][N];

auto prim() -> int
/*
特定の頂点 u に訪問した時にそれまでに考慮した頂点全てを通った場合に最小値になるように dst
を保持しつつ全域木を作成
*/
{
  Color color[N];
  int dst[N], p[N], u, minv;
  lp(i, n) dst[i] = INF, p[i] = -1, color[i] = Color::White;

  dst[0] = 0;
  while (true) {
    minv = INF;
    u = -1;
    // 探索中（Color::Grey）の頂点のうち最小の重みを持つ頂点から順に片付ける.
    lp(i, n) if (minv > dst[i] && color[i] != Color::Black) u = i, minv = dst[i];
    if (u == -1)
      break;
    color[u] = Color::Black;
    // この回で決めた頂点 u から隣接してる頂点 (|V|)を探索中の頂点として Color::Grey にしつつ、
    // これまでの重みの最小値と u - v 間 の新しい重みを比較して小さい方を dst 保管.
    lp(v, n) if (color[v] != Color::Black && mat[u][v] != NOT_CONNECTED) if (dst[v] > mat[u][v])
        dst[v] = mat[u][v],
        p[v] = u, color[v] = Color::Grey;
  }

  int sum = 0;
  //  node への parent が存在する -> 訪問済み
  //　parent からその node へ訪問する（最小の path を通る）さいの cost の総和を求める.
  lp(i, n) if (p[i] != -1) sum += mat[i][p[i]];
  return sum;
}

void create_adj_mat()
{
  int u, e;
  cin >> n;
  lp(i, n) lp(j, n) cin >> e, mat[i][j] = (e == -1) ? NOT_CONNECTED : e;
}

auto main() -> int
{
  create_adj_mat();
  cout << prim() << endl;
  return 0;
}