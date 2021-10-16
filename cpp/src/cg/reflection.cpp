#include <algorithm>
#include <cmath>
#include <iostream>
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
  auto operator<(const Point &p) -> bool { return x != p.x ? x < p.x : y < p.y; }
  auto operator==(const Point &p) -> bool { return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS; }

  auto abs() -> double { return sqrt(norm()); }
  auto norm() -> double { return x * x + y * y; }
};

using Vector = Point;
struct Segment {
  Point p1, p2;
};

auto dot(Vector a, Vector b) -> double { return a.x * b.x + a.y * b.y; }
auto cross(Vector a, Vector b) -> double { return a.x * b.y - a.y * b.x; }

auto project(Segment &s, Point &p) -> Point
{
  Vector base = s.p2 - s.p1;
  double r = dot(p - s.p1, base) / base.norm();
  return s.p1 + base * r;
}

auto reflection(Segment s, Point p) -> Point { return p + (project(s, p) - p) * 2; }

auto main() -> int
{
  int n;
  Segment s;
  Point p;
  scanf("%lf %lf %lf %lf", &s.p1.x, &s.p1.y, &s.p2.x, &s.p2.y);

  cin >> n;
  lp(i, n)
  {
    scanf("%lf %lf", &p.x, &p.y);
    auto ref_p = reflection(s, p);

    printf("%.10lf %.10lf\n", ref_p.x, ref_p.y);
  }
  return 0;
}