/*
Simple problem <src/dsl/disjoint_set.cpp>
Useful ref to understand <https://algo-logic.info/kruskal-mst/>
*/
#include <algorithm>
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
  // rank が低い方の木を高い方へリンクする.
  // リンクする: 低い方の rep の親を高い方の rep にする
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

class Edge {
public:
  int source, target, cost;
  Edge(int source = 0, int target = 0, int cost = 0) : source(source), target(target), cost(cost) {}
  auto operator<(const Edge &e) const -> bool { return cost < e.cost; }
};

auto kruskal(int n, vector<Edge> &edges) -> int
{
  int sum = 0;
  sort(edges.begin(), edges.end()); // 辺を cost 順にソート.
  DisjointSet dset = DisjointSet(n + 1);
  lp(i, n) dset.makeSet(i);

  int source, target;
  // 閉路ができてしまうかどうか = その component の rep が同じかどうか.
  for (auto &e : edges)
    if (!dset.same(e.source, e.target))
      sum += e.cost, dset.unite(e.source, e.target);
  return sum;
}

auto main() -> int
{
  int n, m, cost, source, target;
  cin >> n >> m;
  vector<Edge> edges;
  lp(i, m) cin >> source >> target >> cost, edges.emplace_back(source, target, cost);

  cout << kruskal(n, edges) << endl;
  return 0;
}