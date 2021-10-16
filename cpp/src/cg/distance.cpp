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

auto get_distance(Point a, Point b) -> double { return abs(a - b); }
auto get_distance_lp(Line l, Point p) -> double
// 点と直線の距離 (p381)
// ベクトル a,b から成る平行四辺形（parallelogram）の高さ d (=|axb|/|a|)
{
  return abs(cross(l.p2 - l.p1, p - l.p1) / abs(l.p2 - l.p1));
}
auto get_distance_sp(Segment s, Point p) -> double
/*
線分の場合は、３の場合分け:
1. ベクトル p1-p2 と p-p1 の成す各θが 90 度より大きい（または、-90 度より小さい)
2. ベクトル p2-p1 と p-p2 の成す各θが 90 度より大きい（または、-90 度より小さい)
3. それ以外
場合分けするのは、線分なので垂線が引けない Point p が十分に考えられるため.
*/
{
  if (dot(s.p2 - s.p1, p - s.p1) < 0.0)
    return abs(p - s.p1);
  if (dot(s.p1 - s.p2, p - s.p2) < 0.0)
    return abs(p - s.p2);
  return get_distance_lp(s, p);
}
auto intersect(Point p1, Point p2, Point p3, Point p4) -> bool { return true; }
auto intersect(Segment s1, Segment s2) -> bool { return intersect(s1.p1, s1.p2, s2.p1, s2.p2); }
auto get_distance(Segment s1, Segment s2) -> double
/*
線分どうしの距離は、線分 s1,w2 の p1/p2,p3/p4 いずれかの端点から
もう一方の線分までの最短距離
*/
{
  if (intersect(s1, s2))
    return 0.0;
  return min(min(get_distance_sp(s1, s2.p1), get_distance_sp(s1, s2.p2)),
             min(get_distance_sp(s2, s1.p1), get_distance_sp(s2, s1.p2)));
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
    auto d = get_distance(s1, s2);

    printf("%.10lf\n", d);
  }
  return 0;
}