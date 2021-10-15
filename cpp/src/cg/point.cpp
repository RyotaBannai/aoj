#include <cmath>
#define EPS (1e-10)
#define equals(a, b) (fabs((a) - (b)) < EPS) // fabs 算術型の絶対値を求める.

class Point {
public:
  double x, y;
  Point(double x = 0, double y = 0) : x(x), y(y) {}
  auto operator+(Point p) const -> Point { return Point{x + p.x, y + p.y}; }
  auto operator-(Point p) const -> Point { return Point{x - p.x, y - p.y}; }
  auto operator*(double a) const -> Point { return Point{x * a, y * a}; }
  auto operator/(double a) const -> Point { return Point{x / a, y / a}; }

  auto abs() -> double { return sqrt(norm()); }
  auto norm() -> double { return x * x + y * y; } // 大きさの 2 常を返す

  auto operator<(const Point &p) -> bool { return x != p.x ? x < p.x : y < p.y; }
  auto operator==(const Point &p) -> bool { return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS; }
};

using Vector = Point;

auto dot(Vector v1, Vector v2) -> double { return v1.x * v2.x + v1.y * v2.y; }
auto cross(Vector v1, Vector v2) -> double { return v1.x * v2.y - v1.y * v2.x; }