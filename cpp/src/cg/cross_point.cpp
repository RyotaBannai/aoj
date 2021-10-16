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
};
struct Segment {
  Point p1, p2;
};
using Vector = Point;
using Line = Segment;

auto norm(Point p) -> double { return p.x * p.x + p.y * p.y; }
auto abs(Point p) -> double { return sqrt(norm(p)); }
auto dot(Vector a, Vector b) -> double { return a.x * b.x + a.y * b.y; }
auto cross(Vector a, Vector b) -> double { return a.x * b.y - a.y * b.x; }
auto cross_point(Segment s1, Segment s2) -> Point
{
  Vector base = s2.p2 - s2.p1;
  Vector hypo1 = s1.p1 - s2.p1;
  Vector hypo2 = s2.p2 - s1.p2;
  // |base x hypo1| '外積'の結果の'大きさ' 分母の base は t で約分されるため省略.
  double d1 = abs(cross(base, hypo1));
  // |base x hypo2|
  double d2 = abs(cross(base, hypo2));
  double t = d1 / (d1 + d2);
  return s1.p1 + (s1.p2 - s1.p1) * t;
}

auto main() -> int
{
  int n;
  Segment s1;
  Segment s2;

  cin >> n;
  lp(i, n)
  {
    scanf("%lf %lf %lf %lf", &s1.p1.x, &s1.p1.y, &s1.p2.x, &s1.p2.y);
    scanf("%lf %lf %lf %lf", &s2.p1.x, &s2.p1.y, &s2.p2.x, &s2.p2.y);
    auto cross_p = cross_point(s1, s2);
    printf("%.10lf %.10lf\n", cross_p.x, cross_p.y);
  }
  return 0;
}