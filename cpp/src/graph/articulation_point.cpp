#include <iostream>
#include <set>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
#define lps(i, j, n) for (int i = j; i < n; i++)
using namespace std;
static const int MAX = 10000;

vector<int> g[MAX];
bool visited[MAX];
int prenum[MAX], parent[MAX], lowest[MAX], timer, n;

void dsf(int current, int prev)
{
  prenum[current] = lowest[current] = timer;
  timer++;
  visited[current] = true;

  for (auto &next : g[current]) {
    if (!visited[next]) {
      parent[next] = current;
      dsf(next, current);
      lowest[current] = min(lowest[current], lowest[next]);
    }
    else if (next != prev) {
      lowest[current] = min(lowest[current], prenum[next]);
    }
  }
}

void art_point()
{
  lp(i, n) visited[i] = false;
  timer = 1;
  dsf(0, -1); // lowest の計算

  set<int> ap;
  int np = 0;
  lps(i, 1, n)
  {
    int p = parent[i];
    if (p == 0)
      np++;
    else if (prenum[p] <= lowest[i])
      ap.insert(p);
  }
  if (np > 1)
    ap.insert(0);
  for (auto &x : ap)
    cout << x << endl;
}

auto main() -> int
{
  int m, s, t;
  cin >> n >> m;
  lp(i, m) cin >> s >> t, g[s].push_back(t), g[t].push_back(s); // 無向
  art_point();

  return 0;
}