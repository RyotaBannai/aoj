#include <iostream>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;

static const int NMAX = 105;
static const int WMAX = 10005;
static const int DIAGONAL = 1;
static const int TOP = 0;
int N, W;

struct Item {
  int v, w;
  Item() = default;
  Item(int v, int w) : v(v), w(w) {}
};

vector<Item> items;
int c[NMAX + 1][WMAX + 1], g[NMAX + 1][WMAX + 1];

void compute(int &maxv, vector<int> &selection)
{
  lp(w, W + 1)
  {
    c[0][w] = 0;
    g[0][w] = DIAGONAL;
  }
}

auto main() -> int
{
  int v, w, maxv;
  vector<int> selection;
  cin >> N >> W;
  lp(i, N) cin >> v >> w, items.emplace_back(v, w);
  compute(maxv, selection);
}