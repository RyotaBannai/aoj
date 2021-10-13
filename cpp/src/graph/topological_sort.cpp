#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;
static const int MAX = 10000;
static const int INF = 1 << 21;

int n, indeg[MAX]; // indeg 入次数（前のタスクが完了した時 -1）
vector<int> g[MAX];
list<int> out;
bool v[MAX];

void bfs(int s)
{
  queue<int> q;
  v[s] = true, q.push(s); // タスク完了フラグ
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    out.push_back(u);
    for (auto &x : g[u])
      if ((--indeg[x]) == 0 && !v[x])
        v[x] = true, q.push(x); // タスク完了フラグ
  }
}

void tsort()
{
  for (auto &x : indeg)
    x = 0;
  lp(u, n) for (auto &v : g[u]) indeg[v]++;

  lp(u, n) if (indeg[u] == 0 && !v[u]) bfs(u); // 訪問準備ができている and まだ完了していない
  for (auto &x : out)
    cout << x << endl;
}

auto main() -> int
{
  int s, t, m;
  cin >> n >> m;

  lp(i, n) v[i] = false;
  lp(i, m) cin >> s >> t, g[s].push_back(t); // 隣接リストを構築
  tsort();

  return 0;
}