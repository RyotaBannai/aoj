#include <iostream>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;

enum class Color { White, Grey, Black };
static const int N = 100;
static const int INF = 1 << 21, NOT_CONNECTED = INF;
int n, mat[N][N];

void create_adj_mat()
{
  int id, k, v, c;
  cin >> n;

  lp(i, n) lp(j, n) mat[i][j] = INF;
  lp(i, n)
  {
    cin >> id >> k;
    lp(j, k) cin >> v >> c, mat[id][v] = c;
  }
}

void dijkstra()
{
  int minv, maybe_min_dv;
  int d[N];
  Color color[N];

  lp(i, n) d[i] = INF, color[i] = Color::White;
  d[0] = 0;
  color[0] = Color::Grey;
  while (true) {
    minv = INF;
    int u = -1;
    lp(i, n) if (minv > d[i] && color[i] != Color::Black) u = i, minv = d[i];
    if (u == -1)
      break;
    color[u] = Color::Black;
    lp(v, n) if (color[v] != Color::Black && mat[u][v] != NOT_CONNECTED &&
                 d[v] > (maybe_min_dv = d[u] + mat[u][v]))
    {
      d[v] = maybe_min_dv;
      color[v] = Color::Grey;
    }
  }
  lp(i, n) cout << i << " " << (d[i] == NOT_CONNECTED ? -1 : d[i]) << endl;
}

auto main() -> int
{
  create_adj_mat();
  dijkstra();
  return 0;
}