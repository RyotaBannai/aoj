#include <algorithm>
#include <complex>
#include <iostream>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;

struct P {
  int x, y;
  P() = default;
  P(int x, int y) : x(x), y(y) {}
};

auto operator<(const P &a, const P &b) -> bool { return a.x != b.x ? a.x < b.x : a.y < b.y; }
auto operator-(const P &a, const P &b) -> P { return P{a.x - b.x, a.y - b.y}; }
auto dot(const P &a, const P &b) -> int { return a.x * b.x + a.y * b.y; }
auto cross(const P &a, const P &b) -> int { return a.x * b.y - a.y * b.x; }
auto norm(const P &p) -> int { return p.x * p.x + p.y * p.y; }

auto ccw(P a, P b, P c) -> int
{
  b = b - a;
  c = c - a;

  if (cross(b, c) > 0) // counter
    return +1;
  if (cross(b, c) < 0) // clock
    return -1;
  if (dot(b, c) < 0) // back
    return +2;
  if (norm(b) < norm(c)) // front
    return +2;

  return 0; // segment
}

auto convex_hull(vector<P> ps) -> vector<P>
{
  int n = ps.size();

  sort(ps.begin(), ps.end());

  vector<P> u, l;
  u.push_back(ps[0]), u.push_back(ps[1]), l.push_back(ps[n - 1]), l.push_back(ps[n - 2]);

  for (int i = 2; i < n; i++) {
    for (int n = u.size(); n >= 2 && ccw(u[n - 2], u[n - 1], ps[i]) == 1; n--)
      u.pop_back();
    u.push_back(ps[i]);
  }

  for (int i = n - 3; i >= 0; i--) {
    for (int n = l.size(); n >= 2 && ccw(l[n - 2], l[n - 1], ps[i]) == 1; n--)
      l.pop_back();
    l.push_back(ps[i]);
  }

  reverse(l.begin(), l.end());
  for (int i = u.size() - 2; i >= 1; i--)
    l.push_back(u[i]);

  return l;
}

auto main() -> int
{
  int n, x, y;
  vector<P> points;

  cin >> n;
  lp(i, n) cin >> x >> y, points.emplace_back(x, y);

  auto ch = convex_hull(points);

  auto i = min_element(ch.begin(), ch.end(),
                       [](const P &a, const P &b) { return a.y != b.y ? a.y < b.y : a.x < b.x; }) -
           ch.begin();

  cout << ch.size() << endl;
  for (int j = 0; j < ch.size(); j++)
    cout << ch[(i + j) % ch.size()].x << " " << ch[(i + j) % ch.size()].y << endl;
}
