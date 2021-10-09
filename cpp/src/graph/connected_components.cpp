#include <iostream>
#include <stack>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
#define pb push_back
using namespace std;

static const int N = 100;
static const int NIL = -1;

vector<int> g[N];
int color[N];
int n;

void dfs(int r, int c)
{
  stack<int> stk;
  stk.push(r);
  color[r] = c;

  int u;
  while (!stk.empty()) {
    u = stk.top(), stk.pop();
    for (auto &v : g[u])
      if (color[v] == NIL)
        color[v] = c, stk.push(v);
  }
}

void assign_color()
{
  int id = 1;
  lp(i, n) color[i] = NIL;
  // 全 vertex が繋がっている場合は color の id は全て同じ
  lp(u, n) if (color[u] == NIL) dfs(u, id++);
}

void adj_list()
{
  int s, t, m;
  cin >> n >> m;
  lp(i, m) cin >> s >> t, g[s].pb(t), g[t].pb(s); // 無向グラフ
  assign_color();
}

void solve()
{
  int s, t, q;
  cin >> q;

  lp(i, q) cin >> s >> t, cout << (color[s] == color[t] ? "yes" : "no") << endl;
}

auto main() -> int
{
  adj_list();
  solve();

  return 0;
}