#include <algorithm>
#include <iostream>
#include <set>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;
static const int N = 8;
static const int FREE = -1;
static const int NOT_FREE = 1;

int row[N], col[N], dpos[2 * N - 1], dneg[2 * N - 1];
struct Tile {
  int r, c;
  Tile(int r, int c) : r(r), c(c) {}
  auto operator<(const Tile &t) const -> bool { return r != t.r ? r < t.r : c < t.c; }
};
set<Tile> X;

auto ll(int i, int j) -> int { return i + j; }
auto rl(int i, int j) -> int { return i - j + N - 1; }
void add(int i, int j) { row[i] = j, col[j] = dpos[ll(i, j)] = dneg[rl(i, j)] = NOT_FREE; }
void remove(int i, int j) { row[i] = col[j] = dpos[ll(i, j)] = dneg[rl(i, j)] = FREE; }

void print()
{
  /*
  8queens problem は解は一意になる（？）
  backtrack した際に add したマスが remove され結果に反映されないため再追加.
  一意に決まらない場合は初めに追加する意味がないため再検討.
  */
  for (auto t : X)
    add(t.r, t.c);
  lp(i, N)
  {
    lp(j, N) cout << (row[i] == j ? "Q" : ".");
    cout << endl;
  }
}

void solve(int i)
{
  if (i == N) {
    print();
    return;
  }
  else if (find_if(X.begin(), X.end(), [&](const Tile &t) { return t.r == i; }) != X.end())
    solve(i + 1);

  lp(j, N)
  {
    if (NOT_FREE == col[j] || NOT_FREE == dpos[ll(i, j)] || NOT_FREE == dneg[rl(i, j)])
      continue;
    add(i, j);
    solve(i + 1);
    remove(i, j);
  }
}

void init()
{
  lp(i, N) row[i] = col[i] = FREE;
  lp(i, N * 2 - 1) dpos[i] = dneg[i] = FREE;
}

auto main() -> int
{
  int k, r, c;
  cin >> k;

  init();
  lp(i, k) cin >> r >> c, add(r, c), X.insert(Tile{r, c}); // 初期配置

  solve(0);
}