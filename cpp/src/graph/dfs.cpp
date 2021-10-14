#include <array>
#include <iostream>
#include <stack>
#define lp(i, n) for (int i = 0; i < n; i++)
#define lps(i, j, n) for (int i = j; i < n; i++)
using namespace std;

enum class Color { White, Grey, Black };
static const int N = 100;
array<array<int, N + 1>, N + 1> mat{};
array<Color, N> color;
array<int, N> d, f, nt;
int n, ts; // ts := timestamp

auto next(int u) -> int
/*
v を回して隣接行列を探索し、連結している頂点を探す.
nt はその頂点における訪問済みの index. 全て訪問済みの場合は -1
*/
{
  lps(v, nt[u], n)
  {
    nt[u] = v + 1;
    if (mat[u][v])
      return v;
  }
  return -1;
}

void dis_visit(int r)
{
  stack<int> stk;
  stk.push(r);
  color[r] = Color::Grey;
  d[r] = ++ts;

  while (!stk.empty()) {
    int u = stk.top();
    int v = next(u);
    if (v != -1) {
      if (color[v] == Color::White) { // Color::Grey なら pass
        color[v] = Color::Grey;
        d[v] = ++ts;
        stk.push(v);
      }
    }
    else {
      // 末端にある edge などは、隣接 edge が全て Color::Grey になるケースが高く loop
      // の全ての回で処理されずにこの else 文に入り、pop するだけの処理になることが想定される
      stk.pop();
      color[u] = Color::Black;
      f[u] = ++ts;
    }
  }
}

void dfs()
{
  color.fill(Color::White);
  nt.fill(0);
  ts = 0;

  // 未訪問の u を視点として深さ優先探索 （全 vertex が繋がっている場合はこの lp は不要.）
  lp(u, n) if (color[u] == Color::White) dis_visit(u);
  lp(i, n) cout << i + 1 << " " << d[i] << " " << f[i] << endl;
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

auto main() -> int
{
  create_adj_mat();
  dfs();

  return 0;
}