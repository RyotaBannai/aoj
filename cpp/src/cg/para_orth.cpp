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
  Point(double x = 0, double y = 0) : x(x), y(y) {}
  auto operator+(Point p) const -> Point { return Point{x + p.x, y + p.y}; }
  auto operator-(Point p) const -> Point { return Point{x - p.x, y - p.y}; }
  auto operator*(double a) const -> Point { return Point{x * a, y * a}; }
  auto operator/(double a) const -> Point { return Point{x / a, y / a}; }

  auto abs() -> double { return sqrt(norm()); }
  auto norm() -> double { return x * x + y * y; }

  auto operator<(const Point &p) -> bool { return x != p.x ? x < p.x : y < p.y; }
  auto operator==(const Point &p) -> bool { return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS; }
};

using Vector = Point;
struct Segment {
  Point p1, p2;
};

auto dot(Vector a, Vector b) -> double { return a.x * b.x + a.y * b.y; }
auto cross(Vector a, Vector b) -> double { return a.x * b.y - a.y * b.x; }

// 2 つのベクトル a,b が直行する時、ベクトル a,b の内積は 0
auto is_orth(Vector a, Vector b) -> bool { return equals(dot(a, b), 0.0); }
auto is_orth(Point a1, Point a2, Point b1, Point b2) -> bool { return is_orth(a1 - a2, b1 - b2); }
auto is_orth(Segment s1, Segment s2) -> bool
{
  return equals(dot(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0);
}
// 2 つのベクトル a,b が平行、ベクトル a,b の外積は 0
auto is_para(Vector a, Vector b) -> bool { return equals(cross(a, b), 0.0); }
auto is_para(Point a1, Point a2, Point b1, Point b2) -> bool { return is_para(a1 - a2, b1 - b2); }
auto is_para(Segment s1, Segment s2) -> bool
{
  return equals(cross(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0);
}

auto main() -> int
{
  int n, a1, a2, b1, b2, c1, c2, d1, d2;
  cin >> n;
  lp(i, n)
  {
    cin >> a1 >> a2 >> b1 >> b2 >> c1 >> c2 >> d1 >> d2;
    if (is_orth(Point(a1, a2), Point(b1, b2), Point(c1, c2), Point(d1, d2)))
      cout << "1" << endl;
    else if (is_para(Point(a1, a2), Point(b1, b2), Point(c1, c2), Point(d1, d2)))
      cout << "2" << endl;
    else
      cout << "0" << endl;
  }

  return 0;
}