#include <iostream>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;

class Node {
public:
  int location, parent, left, right;
  Node() = default;
};

class Point {
public:
  int id, x, y;
  Point() = default;
  Point(int id, int x, int y) : id(id), x(x), y(y) {}
  auto operator<(const Point &p) -> const bool { return id < p.id; }
  void print() { printf("%d\n", id); }
};

static const int MAX = 1000000;
static const int NIL = -1;

int n, np;
Point points[MAX];
Node t[MAX];

auto less_x(const Point &p1, const Point &p2) -> bool { return p1.x < p2.x; }
auto less_y(const Point &p1, const Point &p2) -> bool { return p1.y < p2.y; }

auto make_kd_tree(int l, int r, int depth) -> int
{
  if (!(l < r))
    return NIL;
  sort(points + l, points + r, depth % 2 == 0 ? less_x : less_y);

  int mid = (l + r) / 2;
  int v = np++;
  t[v].location = mid;
  t[v].left = make_kd_tree(l, mid, depth + 1);
  t[v].right = make_kd_tree(mid + 1, r, depth + 1);

  return v;
}

void find(int v, int sx, int tx, int sy, int ty, int depth, vector<Point> &ans)
{
  int x = points[t[v].location].x;
  int y = points[t[v].location].y;

  if (sx <= x && x <= tx && sy <= y && y <= ty)
    ans.push_back(points[t[v].location]);

  if (depth % 2 == 0) {
    if (t[v].left != NIL)
      if (sx <= x)
        find(t[v].left, sx, tx, sy, ty, depth + 1, ans);
    if (t[v].right != NIL)
      if (x <= tx)
        find(t[v].right, sx, tx, sy, ty, depth + 1, ans);
  }
  else {
    if (t[v].left != NIL)
      if (sy <= y)
        find(t[v].left, sx, tx, sy, ty, depth + 1, ans);
    if (t[v].right != NIL)
      if (y <= ty)
        find(t[v].right, sx, tx, sy, ty, depth + 1, ans);
  }
}

auto main() -> int
{
  int x, y;
  scanf("%d", &n);
  lp(i, n)
  {
    scanf("%d %d", &x, &y);
    points[i] = Point(i, x, y);
    t[i].left = t[i].right = t[i].parent = NIL;
  }

  np = 0;
  int root = make_kd_tree(0, n, 0);
  int q;
  scanf("%d", &q);
  int sx, tx, sy, ty;
  vector<Point> ans;
  lp(i, 1)
  {
    scanf("%d %d %d %d", &sx, &tx, &sy, &ty);
    ans.clear();
    find(root, sx, tx, sy, ty, 0, ans);
    for (auto &a : ans)
      a.print();
    printf("\n");
  }

  return 0;
}