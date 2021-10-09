#include <array>
#include <iostream>
#include <queue>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;

static const int N = 100;
static const int INF = 1 << 21;

array<array<int, N + 1>, N + 1> mat{};
array<int, N> dist;
int n;

void bfs(int s)
{
  queue<int> q;
  q.push(s);
  dist.fill(INF);
  dist[s] = 0; // 移動距離 0
  int u;

  while (!q.empty()) {
    u = q.front();
    q.pop();
    lp(v, n)
    {
      if (mat[u][v] == 0) // 連接してない
        continue;
      if (dist[v] != INF) // すでに訪問済み
        continue;
      dist[v] = dist[u] + 1;
      q.push(v);
    }
  }
}

void create_adj_mat()
{
  int u, v, k;
  cin >> n;

  lp(i, n)
  {
    cin >> u >> k;
    --u;
    lp(j, k)
    {
      cin >> v;
      mat[u][--v] = 1;
    }
  }
}

void format() { lp(i, n) cout << i + 1 << " " << (dist[i] == INF ? (-1) : dist[i]) << endl; }

auto main() -> int
{
  create_adj_mat();
  bfs(0);
  format();

  return 0;
}