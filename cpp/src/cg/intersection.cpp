#include <algorithm>
#include <cmath>
#include <iostream>
#define lp(i, n) for (int i = 0; i < n; i++)
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

enum class Clock : int {
  COUNTER_CLOCKWISE = 1,
  CLOCKWISE = -1,
  ONLINE_BACK = 2,
  ONLINE_FRONT = -2,
  ON_SEGMENT = 0
};
// https://qiita.com/yumetodo/items/6f7b5c3714b821fe0196#c11%E3%81%AB%E3%81%AFenum-class%E3%81%8C%E3%81%82%E3%82%8B
constexpr auto operator*(Clock l, Clock r) -> int
{
  // return static_cast<Clock>(static_cast<int>(l) * static_cast<int>(r));
  return static_cast<int>(l) * static_cast<int>(r);
}
constexpr auto operator*(Clock l, int r) -> int
{
  // return static_cast<Clock>(static_cast<int>(l) * r);
  return static_cast<int>(l) * r;
}
constexpr auto operator*(int l, Clock r) -> int
{
  // return static_cast<Clock>(l * static_cast<int>(r));
  return l * static_cast<int>(r);
}

auto ccw(Point p0, Point p1, Point p2) -> Clock
{
  Vector v1 = p2 - p1;
  Vector v2 = p0 - p1;
  if (cross(v1, v2) > EPS)
    return Clock::COUNTER_CLOCKWISE;
  else if (cross(v1, v2) < -EPS)
    return Clock::CLOCKWISE;
  else if (dot(v1, v2) < -EPS)
    return Clock::ONLINE_BACK;
  else
    return norm(v2) > norm(v1) ? Clock::ONLINE_FRONT : Clock::ON_SEGMENT;
}
auto intersect(Point p1, Point p2, Point p3, Point p4) -> bool
{
  return (ccw(p3, p1, p2) * ccw(p4, p1, p2) <= 0) && (ccw(p1, p3, p4) * ccw(p2, p3, p4) <= 0);
}
auto intersect(Segment s1, Segment s2) -> bool { return intersect(s1.p1, s1.p2, s2.p1, s2.p2); }

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
    cout << (intersect(s1, s2) ? "1" : "0") << endl;
  }
  return 0;
}