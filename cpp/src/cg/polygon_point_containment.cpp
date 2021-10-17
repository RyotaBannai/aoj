#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#define EPS (1e-10)
#define lp(i, n) for (int i = 0; i < n; i++)
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
using Vector = Point;
using Polygon = vector<Point>;

auto norm(Point p) -> double { return p.x * p.x + p.y * p.y; }
auto abs(Point p) -> double { return sqrt(norm(p)); }
auto dot(Vector a, Vector b) -> double { return a.x * b.x + a.y * b.y; }
auto cross(Vector a, Vector b) -> double { return a.x * b.y - a.y * b.x; }
auto contains(Polygon g, Point &&p) -> int
{
  int n = g.size();
  bool x = false;
  lp(i, n)
  {
    // 図形なので、i == size の時には、i == 0 の点と繋げるため %n の計算
    Point a = g[i] - p, b = g[(i + 1) % n] - p;
    // ベクトル a,b が同一直線上にあり、かつ向きが反対(180度)の場合
    if (abs(cross(a, b)) < EPS && dot(a, b) < EPS)
      return 1;
    if (a.y > b.y)
      swap(a, b);
    // それぞれのベクトルが半直線を跨いでいる場合（ベクトル a が下向き、ベクトル b が 上向） かつ
    // ベクトル a,b の外積が正である場合
    if (a.y < EPS && EPS < b.y && cross(a, b) > EPS)
      x = !x;
  }
  return (x ? 2 : 0);
}

auto main() -> int
{
  int n, q;
  double x, y;
  Polygon g;

  cin >> n;
  lp(i, n) scanf("%lf %lf", &x, &y), g.emplace_back(x, y);

  cin >> q;
  lp(i, q) scanf("%lf %lf", &x, &y), cout << contains(g, Point{x, y}) << endl;

  return 0;
}