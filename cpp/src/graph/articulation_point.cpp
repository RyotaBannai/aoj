/*
Maybe useful ref |
<https://o-treetree.hatenablog.com/entry/2020/06/08/231258#%E9%96%A2%E7%AF%80%E7%82%B9%E3%81%A8%E6%A9%8B>
*/

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
/*
lowlink を計算する上で次の３パターンから最小値を利用する：
ある頂点 u に対して：
1. prenum[u]
2. G の Backedge(u,v) が存在するとき、頂点 v における prenum[v] (Backege(u,v) とは、頂点 u から T
に属する頂点 v に向かう T に属さない G のエッジ. つまり最短の距離ではないため通らなかった path.
後退辺ともいう.)
3. T に属する頂点 u の全ての子 x に対する lowest[x]

1. は処理を始める時に timer から追加される.
3. は　lowest[current] を計算する前に、next
が再帰によって既に計算済みであるため、全ての子の最小が連鎖的に親まで伝播する
2. Backage かどうかの判定は for と else if で行っている. 無向グラフであれば、u -> v, v -> u の path
が存在し、 仮に for で next が u （親）だった場合、処理を pass する. もし、親以外に path
を持っていれば、Backage であると判定することができるため else if の処理に入れる.
*/
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
    // 訪問済みだが、prev ではない隣接する頂点（edge current -> next が back-edge の場合）
    else if (next != prev) {
      // next == prev の時は、無向グラフの場合や有向グラフで多重辺がある場合に current から
      // current へ辿る前の頂点（prev）への path が含まれるケースが考えられる.
      // このケースを弾かないと、back-edge ではないケースも処理してしまう.
      // (next == prev の path しかない時、その path は back-edge ではない)
      lowest[current] = min(lowest[current], prenum[next]);
    }
  }
}

void art_point()
{
  lp(i, n) visited[i] = false;
  timer = 1;

  // lowest の計算
  dsf(0, -1);

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
    /* edge が 2 つの場合も成立してしまうため:
    2 1
    0 1
    0
    3 点存在し、0 が 2 点以上(np>1)を break する場合だけを考慮
    */
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