#include <iostream>
#include <queue>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;

using Vertex = pair<int, int>;

enum class Color { White, Grey, Black };
static const int N = 10000;
static const int INF = 1 << 21, NOT_CONNECTED = INF;
int n;
vector<Vertex> adj_wl[N];

void adjancet_weighted_list()
{
  int u, id, k, v, c;

  cin >> n;
  lp(i, n)
  {
    cin >> id >> k;
    lp(j, k) cin >> v >> c, adj_wl[id].emplace_back(v, c);
  }
}

void dijkstra()
{
  int minv, maybe_min_dv;
  int d[N];
  Color color[N];
  priority_queue<Vertex> pq;
  Vertex f;

  lp(i, n) d[i] = INF, color[i] = Color::White;
  d[0] = 0;
  pq.emplace(0, 0);
  color[0] = Color::Grey;
  while (!pq.empty()) {
    f = pq.top(), pq.pop(); // - で大小を反転いるが、cost が最小の頂点を取り出す.
    int u = f.second;
    color[u] = Color::Black;
    if (d[u] < f.first * (-1))
      // 最小の頂点から他の頂点へ訪問するために pq
      // に入っているバージョンの訪問中の頂点が既知のその頂点への最小の経路より大きい場合は捨てる
      continue;
    for (auto &x : adj_wl[u]) {
      int v = x.first;
      if (color[v] != Color::Black && d[v] > (maybe_min_dv = d[u] + x.second)) {
        d[v] = maybe_min_dv;
        // 最小の経路を元に訪問した隣接する頂点を始点としてその他の頂点の最短経路の計算を行うため
        // queue に追加
        pq.emplace(d[v] * (-1), v);
        color[v] = Color::Grey;
      }
    }
  }
  lp(i, n) cout << i << " " << (d[i] == NOT_CONNECTED ? -1 : d[i]) << endl;
}

auto main() -> int
{
  adjancet_weighted_list();
  dijkstra();

  return 0;
}