#include <iostream>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;

/*
左子右兄弟表現, left-child, right-sibling representation
  u.parent = Nil `root`
  u.left が存在しない節点 `leaf`
  u.right が存在しない節点 `最も下の子`（兄弟関係において）

・各節（t[n]）の value は一意. ただし、節自体 value を持たずに他の説が t[n]
を親(parent)、または子(left or right)として参照.
*/

struct Node {
  int parent, left, right;
};

const int MAX = 10005; // 100005
const int NIL = -1;
vector<Node> t(MAX);
vector<int> depths(MAX);

void print_vector_int(const vector<int> v)
{
  for (auto x = v.begin(); x != v.end(); ++x)
    cout << *x << (x != --v.end() ? ',' : ' ');
  cout << endl;
}

void format(int u)
{
  int i, c;
  cout << "node " << u << ": ";
  cout << "parent = " << t[u].parent << ", ";
  cout << "depth = " << depths[u] << ", ";

  if (t[u].parent == NIL)
    cout << "root, ";
  else if (t[u].left == NIL)
    cout << "leaf, ";
  else
    cout << "internal node, ";

  cout << "[";
  for (i = 0, c = t[u].left; c != NIL; i++, c = t[c].right) {
    if (i)
      cout << ", ";
    cout << c;
  }
  cout << "]" << endl;
}

void rec(int u, int p)
// 親から、左(left)の子供から right に向かって全ての子を走査（この時に p + 1 で深さを + 1 する）
// その子がまた left を持つ場合も再起的に走査
{
  depths[u] = p;
  if (t[u].right != NIL) // 他に兄弟外いる
    rec(t[u].right, p);
  if (t[u].left != NIL) // 子を持つ
    rec(t[u].left, p + 1);
}

auto main() -> int
{
  int i, j, num, v, c, l, root, n;
  cin >> n;

  lp(i, n) t[i].parent = t[i].left = t[i].right = NIL;
  lp(i, n)
  {
    cin >> v >> num;
    lp(j, num)
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
  lp(i, n) if (t[i].parent == NIL) root = i;
  rec(root, 0);
  lp(i, n) format(i);

  // print_vector_int(depths);

  return 0;
}