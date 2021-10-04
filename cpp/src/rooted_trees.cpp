#include <iostream>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;

/*
左子右兄弟表現, left-child, right-sibling representation
  u.parent = Nil `root`
  u.left が存在しない節点 `leaf`
  u.right が存在しない節点 `最も下の子`
*/

struct Node {
  int parent, left, right;
};

const int MAX = 10005;
const int NIL = -1;
vector<Node> t(MAX), d(MAX);

void format() {}
auto rec(int u, int p) -> int {}

auto main() -> int
{
  int i, j, d, v, c, l, r, n;
  cin >> n;

  lp(i, n) t[i].parent = t[i].left = t[i].right = NIL;
  lp(i, n)
  {
    cin >> v >> d;
    lp(j, d)
    {
      cin >> c;
      if (j == 0)
        t[v].left = c;
      else
        t[l].right = c;

      l = c;
      t[c].parent = v;
    }
  }
  lp(i, n) if (t[i].p == NIL) r = i;

  // rec(r, 0);
  // lp(i, n) format(i);
  return 0;
}