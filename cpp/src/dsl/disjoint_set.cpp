#include <iostream>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;

class DisjointSet {
public:
  vector<int> rank, p;
  DisjointSet() = default;
  DisjointSet(int size)
  {
    rank.resize(size, 0);
    p.resize(size, 0);
    lp(i, size) makeSet(i);
  }
  void makeSet(int x) { p[x] = x, rank[x] = 0; }
  auto same(int x, int y) -> bool { return findSet(x) == findSet(y); }
  void unite(int x, int y) { link(findSet(x), findSet(y)); }
  void link(int x, int y)
  {
    if (rank[x] > rank[y])
      p[y] = x;
    else {
      p[x] = y;
      if (rank[x] == rank[y])
        rank[y]++;
    }
  }
  auto findSet(int x) -> int
  /*
  Disjoint set の representative は root
  最適化のために findSet で rep を見つけた際に、各値が rep への参照を持つ方法がある.
  */
  {
    if (x != p[x]) // root の親は自分自身
      p[x] = findSet(p[x]);
    return p[x];
  }
};

auto main() -> int
{
  int n, a, b, q, t;
  cin >> n >> q;
  DisjointSet ds = DisjointSet(n);

  lp(i, q)
  {
    cin >> t >> a >> b;
    if (t == 0)
      ds.unite(a, b);
    else if (t == 1)
      cout << (ds.same(a, b) ? 1 : 0) << endl;
  }

  return 0;
}