#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#define EPS (1e-10)
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
struct Circle {
  Point c;
  double r;
  Circle(Point c = Point(), double r = 0.0) : c(c), r(r) {}
};
using Vector = Point;

auto norm(Point p) -> double { return p.x * p.x + p.y * p.y; }
auto abs(Point p) -> double { return sqrt(norm(p)); }
auto arg(Vector p) -> double { return atan2(p.y, p.x); }
auto polar(double r, double ta) -> Vector
// check out <https://mathwords.net/heimenkaiten>
// also check out note.
{
  return Point{r * cos(ta), r * sin(ta)};
}
auto cross_points_circles(Circle c1, Circle c2) -> pair<Point, Point>
{
  // assert(intersect(c1,c2));
  double d = abs(c1.c - c2.c);
  double a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d)); // 余弦定理
  double t = arg(c2.c - c1.c);
  vector<Point> ps = {c1.c + polar(c1.r, t + a), c1.c + polar(c1.r, t - a)};
  sort(ps.begin(), ps.end());
  return make_pair(ps[0], ps[1]);
}

auto main() -> int
{
  Circle c1, c2;
  scanf("%lf %lf %lf", &c1.c.x, &c1.c.y, &c1.r);
  scanf("%lf %lf %lf", &c2.c.x, &c2.c.y, &c2.r);
  auto cross_ps = cross_points_circles(c1, c2);
  printf("%.10lf %.10lf %.10lf %.10lf\n", cross_ps.first.x, cross_ps.first.y, cross_ps.second.x,
         cross_ps.second.y);

  return 0;
}