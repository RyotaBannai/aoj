#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
// #define pl(i, n) for (int i = (n - 1); i >= 0; i--)
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
auto operator<<(ostream &os, const Point &p) -> ostream & { return os << p.x << " " << p.y; }
struct Segment {
  Point p1, p2;
};
using Vector = Point;
using Polygon = vector<Point>;

enum class Clock { COUNTER_CLOCKWISE, CLOCKWISE, ONLINE_BACK, ONLINE_FRONT, ON_SEGMENT };

auto norm(Point p) -> double { return p.x * p.x + p.y * p.y; }
auto abs(Point p) -> double { return sqrt(norm(p)); }
auto dot(Vector a, Vector b) -> double { return a.x * b.x + a.y * b.y; }
auto cross(Vector a, Vector b) -> double { return a.x * b.y - a.y * b.x; }

auto ccw(Point p0, Point p1, Point p2) -> Clock
{
  Vector a = p1 - p0;
  Vector b = p2 - p0;
  if (cross(a, b) > EPS)
    return Clock::COUNTER_CLOCKWISE;
  else if (cross(a, b) < -EPS)
    return Clock::CLOCKWISE;
  else if (dot(a, b) < -EPS)
    return Clock::ONLINE_BACK;
  else
    return norm(b) > norm(a) ? Clock::ONLINE_FRONT : Clock::ON_SEGMENT;
}

auto andrew(Polygon s) -> Polygon
{
  Polygon u, l;
  int n = s.size();
  if (n < 3)
    return s;
  sort(s.begin(), s.end());

  u.push_back(s[0]), u.push_back(s[1]), l.push_back(s[n - 1]), l.push_back(s[n - 2]);

  for (int i = 2; i < n; i++) {
    for (int n = u.size(); n >= 2 && ccw(u[n - 2], u[n - 1], s[i]) == Clock::COUNTER_CLOCKWISE; n--)
      u.pop_back();
    u.push_back(s[i]);
  }

  for (int i = n - 3; i >= 0; i--) {
    for (int n = l.size(); n >= 2 && ccw(l[n - 2], l[n - 1], s[i]) == Clock::COUNTER_CLOCKWISE; n--)
      l.pop_back();
    l.push_back(s[i]);
  }

  reverse(l.begin(), l.end());

  for (int i = u.size() - 2; i >= 1; i--)
    l.push_back(u[i]);

  return l;
}

auto main() -> int
{
  int n, x, y;
  Polygon points;

  cin >> n;
  lp(i, n) cin >> x >> y, points.emplace_back(x, y);

  auto ch = andrew(points);

  auto i = min_element(
               ch.begin(), ch.end(),
               [](const Point &a, const Point &b) { return a.y != b.y ? a.y < b.y : a.x < b.x; }) -
           ch.begin();

  cout << ch.size() << endl;
  int cur;
  for (int j = 0; j < ch.size(); j++)
    cur = (i + j) % ch.size(), cout << ch[cur].x << " " << ch[cur].y << endl;
}