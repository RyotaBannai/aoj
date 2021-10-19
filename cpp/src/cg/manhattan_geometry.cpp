#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
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
struct Segment {
public:
  Point p1, p2;
  Segment() = default;
  Segment(Point p1, Point p2) : p1(p1), p2(p2){};
};

auto norm(Point p) -> double { return p.x * p.x + p.y * p.y; }
auto abs(Point p) -> double { return sqrt(norm(p)); }
auto dot(Vector a, Vector b) -> double { return a.x * b.x + a.y * b.y; }
auto cross(Vector a, Vector b) -> double { return a.x * b.y - a.y * b.x; }

/*
ある走査線上で線分（x 座標のの値）の削除、挿入、そして検索が同時に行われる時（~交わっている時）
端点のソートを基準を以下のようにすることで問題を回避:
BOTTOM が二分探索木に insert される前に LEFT で走査するため、交点を見逃してしまう
TOP が LEFT で走査する前に来ため、交点を確認する前に二分探索木から erase されてしまう
*/
enum class END { BOTTOM, LEFT, RIGHT, TOP };
class EndPoint {
public:
  Point p;
  int seg; // 入力線分 id
  END st;  // st := 末端の種類
  EndPoint() = default;
  EndPoint(Point p, int seg, END st) : p(p), seg(seg), st(st){};
  auto operator<(const EndPoint &ep) const -> bool
  {
    // y 座標が小さい順に並べる
    // y 座標が同じ時は、末端の種類順 （enum class END の順）
    return p.y == ep.p.y ? st < ep.st : p.y < ep.p.y;
  }
};

EndPoint ep[2 * 100000];
auto manhattan(vector<Segment> &s) -> int
{
  int n = s.size(), k = 0;
  // 端点 p1, p2 が左下を基準に並ぶように調整
  // if -> 左 else -> 下
  lp(i, n)
  {
    // 水平成分
    if (s[i].p1.y == s[i].p2.y) {
      if (s[i].p1.x > s[i].p2.x)
        swap(s[i].p1, s[i].p2);
      ep[k++] = EndPoint{s[i].p1, i, END::LEFT};
      ep[k++] = EndPoint{s[i].p2, i, END::RIGHT};
    }
    // 垂直成分
    else {
      if (s[i].p1.y > s[i].p2.y)
        swap(s[i].p1, s[i].p2);
      ep[k++] = EndPoint{s[i].p1, i, END::BOTTOM};
      ep[k++] = EndPoint{s[i].p2, i, END::TOP};
    }
  }

  sort(ep, ep + (2 * n)); // 端点２つずつ入っているためちょうど２倍の位置までソート
  set<int> bt;            // 二分探索技
  bt.insert(1000000001); // 番兵
  int cnt = 0;
  lp(i, 2 * n)
  {
    auto e = ep[i].st;
    if (e == END::TOP)
      bt.erase(ep[i].p.x);
    else if (e == END::BOTTOM)
      bt.insert(ep[i].p.x);
    else if (e == END::LEFT) {
      // sort しているため、when ep[i] == LEFT, then ep[i+1] == RIGHT にはならない.
      auto be = bt.lower_bound(s[ep[i].seg].p1.x);
      auto en = bt.upper_bound(s[ep[i].seg].p2.x);
      cnt += distance(be, en);
    }
  }
  return cnt;
}

auto main() -> int
{
  int n;
  double x1, y1, x2, y2;
  vector<Segment> s;

  cin >> n;
  lp(i, n) cin >> x1 >> y1 >> x2 >> y2, s.emplace_back(Point{x1, y1}, Point{x2, y2});
  cout << manhattan(s) << endl;
}