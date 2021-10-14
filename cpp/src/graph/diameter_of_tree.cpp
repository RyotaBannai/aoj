/*
Maybe useful ref | <https://artak.hatenablog.com/entry/2014/02/20/114126>
*/
#include <iostream>
#include <queue>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;
static const int MAX = 100000;
static const int INF = 1 << 30;

class Edge {
public:
  int t, w;
  Edge() = default;
  Edge(int t, int w) : t(t), w(w) {}
};

vector<Edge> g[MAX];
int n, dst[MAX];

void bsf(int s)
// 幅優先探索で root から各頂点までの距離を w をもとに算出
{
  lp(i, n) dst[i] = INF;
  queue<int> q;
  dst[s] = 0, q.push(s);
  int u;
  while (!q.empty()) {
    u = q.front(), q.pop();
    for (Edge &e : g[u])
      if (dst[e.t] == INF)
        dst[e.t] = dst[u] + e.w, q.push(e.t);
  }
}

void solve()
/*
適当な節点 s から最も遠い節点 x から最も遠い節点 y の距離、dst(x,y) は木の直径である
この証明では、dst(u,v) は直径であると仮定して、dst(x,y) は木の直径であると解く.
dst(u,v) と dst(x,y) の節点間の不等式を解くときに、dst(a,b) の a, b の順に注意する:
dst(a,b) = 2 であれば、dst(b,a) は移動向きが異なるため、-2 である. (距離（重み）自体は 2 のまま)
よって dst(a,b) = -dst(b,a) である.
*/
{
  // 適当な始点 s から最も遠い節点 tgt を求める.
  // (ここでは root = 0 からの距離で構築)
  bsf(0);
  int maxv = 0;
  int tgt = 0;
  lp(i, n)
  {
    if (dst[i] == INF)
      continue;
    if (maxv < dst[i])
      maxv = dst[i], tgt = i;
  }

  // さらに、tgt から最も遠い節点 maxv を求める.
  bsf(tgt);
  maxv = 0;
  lp(i, n)
  {
    if (dst[i] == INF)
      continue;

    maxv = max(maxv, dst[i]);
  }

  cout << maxv << endl;
}

auto main() -> int
{
  int s, t, w;
  cin >> n;
  lp(i, n - 1) cin >> s >> t >> w, g[s].emplace_back(t, w), g[t].emplace_back(s, w); // 無向
  solve();
}