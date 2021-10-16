#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
#define EPS (1e-10)
#define equals(a, b) (fabs((a) - (b)) < EPS)
using namespace std;

class Point {
public:
  double x, y;
  Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}
  auto operator+(Point p) const -> Point { return Point{x + p.x, y + p.y}; }
  auto operator-(Point p) const -> Point { return Point{x - p.x, y - p.y}; }
  auto operator*(double a) const -> Point { return Point{x * a, y * a}; }
  auto operator/(double a) const -> Point { return Point{x / a, y / a}; }
  auto operator<(const Point &p) const -> bool { return x != p.x ? x < p.x : y < p.y; }
  auto operator==(const Point &p) const -> bool
  {
    return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS;
  }
};
struct Segment {
  Point p1, p2;
};
struct Circle {
  Point c;
  double r;
  Circle(Point c = Point(), double r = 0.0) : c(c), r(r) {}
};
using Vector = Point;
using Line = Segment;
// using Polygon = vector<Point>;

auto norm(Point p) -> double { return p.x * p.x + p.y * p.y; }
auto abs(Point p) -> double { return sqrt(norm(p)); }
auto dot(Vector a, Vector b) -> double { return a.x * b.x + a.y * b.y; }
auto cross(Vector a, Vector b) -> double { return a.x * b.y - a.y * b.x; }
auto project(Segment &s, Point &p) -> Point
{
  Vector base = s.p2 - s.p1;
  double r = dot(p - s.p1, base) / norm(base);
  return s.p1 + base * r;
}
auto cross_points(Circle c, Line l) -> pair<Point, Point>
{
  // assert(intersect(c,l));
  Vector pr = project(l, c.c);
  Vector e = (l.p2 - l.p1) / abs(l.p2 - l.p1); // 大きさが 1 の単位ベクトル
  double base = sqrt(c.r * c.r - norm(pr - c.c)); // 斜辺（hypotenuse）ピタゴラスの定理より
  // 一点で交わる時は base が 0 になるため、同じ値の pair となる.
  vector<Point> ps = {pr + e * base, pr - e * base};
  sort(ps.begin(), ps.end());
  return make_pair(ps[0], ps[1]);
}

auto main() -> int
{
  int n;
  Circle c;
  Line l;
  scanf("%lf %lf %lf", &c.c.x, &c.c.y, &c.r);
  cin >> n;
  lp(i, n)
  {
    scanf("%lf %lf %lf %lf", &l.p1.x, &l.p1.y, &l.p2.x, &l.p2.y);
    auto cross_ps = cross_points(c, l);
    printf("%.8lf %.8lf %.8lf %.8lf\n", cross_ps.first.x, cross_ps.first.y, cross_ps.second.x,
           cross_ps.second.y);
  }
  return 0;
}