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
vector<Node> t;