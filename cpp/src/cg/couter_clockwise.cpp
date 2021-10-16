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

enum class Clock { COUNTER_CLOCKWISE, CLOCKWISE, ONLINE_BACK, ONLINE_FRONT, ON_SEGMENT };
auto operator<<(ostream &os, const Clock &e) -> ostream &
{
  string str;
  if (e == Clock::COUNTER_CLOCKWISE)
    str = "COUNTER_CLOCKWISE";
  else if (e == Clock::CLOCKWISE)
    str = "CLOCKWISE";
  else if (e == Clock::ONLINE_BACK)
    str = "ONLINE_BACK";
  else if (e == Clock::ONLINE_FRONT)
    str = "ONLINE_FRONT";
  else
    str = "ON_SEGMENT";
  return os << str;
}

auto norm(Point p) -> double { return p.x * p.x + p.y * p.y; }
auto abs(Point p) -> double { return sqrt(norm(p)); }
auto dot(Vector a, Vector b) -> double { return a.x * b.x + a.y * b.y; }
auto cross(Vector a, Vector b) -> double { return a.x * b.y - a.y * b.x; }

auto ccw(Point p0, Point p1, Point p2) -> Clock
// check p387 for details.
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

auto main() -> int
{
  int n;
  Point p0, p1, p2;
  scanf("%lf %lf %lf %lf", &p1.x, &p1.y, &p2.x, &p2.y);
  cin >> n;

  lp(i, n)
  {
    scanf("%lf %lf", &p0.x, &p0.y);
    cout << ccw(p0, p1, p2) << endl;
  }
  return 0;
}