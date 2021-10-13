#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
#define node t[v]
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
  auto operator<(const Point &p) const -> bool { return id < p.id; }
  void print() { printf("%d\n", id); }
};

static const int MAX = 1000000;
static const int NIL = -1;

int n, np;
Point points[MAX];
Node t[MAX];

auto less_x(const Point &p1, const Point &p2) -> bool { return p1.x < p2.x; }
auto less_y(const Point &p1, const Point &p2) -> bool { return p1.y < p2.y; }

auto even(int d) -> bool { return d % 2 == 0; };

auto make_kd_tree(int l, int r, int depth) -> int
{
  if (!(l < r))
    return NIL;

  sort(points + l, points + r, even(depth) ? less_x : less_y);
  int mid = (l + r) / 2;
  int v = np++;
  node.location = mid;
  node.left = make_kd_tree(l, mid, depth + 1);
  node.right = make_kd_tree(mid + 1, r, depth + 1);

  return v;
}

void find(int v, int sx, int tx, int sy, int ty, int depth, vector<Point> &ans)
{
  int x = points[node.location].x;
  int y = points[node.location].y;

  if (sx <= x && x <= tx && sy <= y && y <= ty)
    ans.push_back(points[node.location]);

  auto apply = [&](int idx) { find(idx, sx, tx, sy, ty, depth + 1, ans); };

  if (even(depth)) {
    if (node.left != NIL && sx <= x)
      apply(node.left);
    if (node.right != NIL && x <= tx)
      apply(node.right);
  }
  else {
    if (node.left != NIL && sy <= y)
      apply(node.left);
    if (node.right != NIL && y <= ty)
      apply(node.right);
  }
}

void create_points()
{
  int x, y;
  scanf("%d", &n);
  lp(i, n)
  {
    scanf("%d %d", &x, &y);
    points[i] = Point(i, x, y);
    t[i].left = t[i].right = t[i].parent = NIL;
  }
}

void solve(int root)
{
  int q, sx, tx, sy, ty;
  scanf("%d", &q);
  vector<Point> ans;
  lp(i, q)
  {
    scanf("%d %d %d %d", &sx, &tx, &sy, &ty);
    ans.clear();
    find(root, sx, tx, sy, ty, 0, ans);
    sort(ans.begin(), ans.end());
    for (auto &a : ans)
      a.print();
    printf("\n");
  }
}

auto main() -> int
{
  create_points();

  np = 0;
  solve(make_kd_tree(0, n, 0));

  return 0;
}