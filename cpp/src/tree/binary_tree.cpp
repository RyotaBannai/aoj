#include <cstdio>
#include <iostream>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
#define node t[u]
using namespace std;

const int MAX = 10000;
const int NIL = -1;

struct Node {
  int parent, left, right;
};

vector<Node> t(MAX);
vector<int> depths(MAX), heights(MAX);

void set_depth(int u, int d)
{
  if (u == NIL)
    return;
  depths[u] = d;
  set_depth(node.left, d + 1);
  set_depth(node.right, d + 1);
}

auto set_height(int u) -> int
{
  int h1 = 0, h2 = 0;
  if (node.left != NIL)
    h1 = set_height(node.left) + 1;

  if (node.right != NIL)
    h2 = set_height(node.right) + 1;

  return heights[u] = (h1 > h2 ? h1 : h2);
}

// 節点 u の兄弟を探す
// parent へ登って他方の値と比較
auto get_sibling(int u) -> int
{
  int ll, rr;
  if (node.parent == NIL)
    return NIL;
  if ((ll = t[node.parent].left) != u && ll != NIL)
    return ll;
  if ((rr = t[node.parent].right) != u && rr != NIL)
    return rr;

  return NIL;
}

void format(int u)
{
  printf("node %d: ", u);
  printf("parent = %d, ", node.parent);
  printf("sibling = %d, ", get_sibling(u));
  int deg = 0;

  if (node.left != NIL)
    deg++;
  if (node.right != NIL)
    deg++;
  printf("degree = %d, ", deg);
  printf("depth = %d, ", depths[u]);
  printf("height = %d, ", heights[u]);

  if (node.parent == NIL)
    printf("root\n");

  else if (node.left == NIL && node.right == NIL)
    printf("leaf\n");
  else
    printf("internal node\n");
}

auto main() -> int
{
  int n, i, u, l, r, root = 0;
  cin >> n;

  lp(u, n) node.parent = NIL;
  lp(u, n)
  {
    cin >> i >> l >> r;
    node.left = l;
    node.right = r;
    if (l != NIL)
      t[l].parent = i;
    if (r != NIL)
      t[r].parent = i;
  }

  lp(u, n) if (node.parent == NIL) root = u;

  set_depth(root, 0);
  set_height(root);
  lp(i, n) format(i);

  return 0;
}
