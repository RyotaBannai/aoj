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

// 先行順巡回
void pre_parse(int u)
{
  if (u == NIL)
    return;
  printf(" %d", u);
  pre_parse(node.left);
  pre_parse(node.right);
}

// 中間順巡回
void in_parse(int u)
{
  if (u == NIL)
    return;
  in_parse(node.left);
  printf(" %d", u);
  in_parse(node.right);
}

// 後行順巡回
void post_parse(int u)
{
  if (u == NIL)
    return;
  post_parse(node.left);
  post_parse(node.right);
  printf(" %d", u);
}

auto main() -> int
{
  int n, u, l, r, root = 0;
  cin >> n;

  lp(i, n) t[i].parent = NIL;
  lp(i, n)
  {
    cin >> u >> l >> r;
    node.left = l;
    node.right = r;
    if (l != NIL)
      t[l].parent = u;
    if (r != NIL)
      t[r].parent = u;
  }

  lp(i, n) if (t[i].parent == NIL) root = i;

  printf("Preorder\n");
  pre_parse(root);
  printf("\nInorder\n");
  in_parse(root);
  printf("\nPostorder\n");
  post_parse(root);
  printf("\n");

  return 0;
}
