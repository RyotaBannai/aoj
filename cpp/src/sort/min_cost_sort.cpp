#include <algorithm>
#include <iostream>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)

using namespace std;

const int max_v = 10000;

template <typename C> void print_vector_int(const C v)
{
  for (auto x = v.begin(); x != v.end(); ++x)
    cout << *x << (x != --v.end() ? ',' : ' ');
  cout << endl;
}

auto solve(vector<int> &a, int n, int s) -> int
{
  int ans = 0, i = 0;
  vector<int> b(a.size()), t(max_v + 1);
  vector<bool> bs(a.size(), false);

  b = a;                    // a = 1,5,3,4,2
  sort(b.begin(), b.end()); // b = 1,2,3,4,5
  lp(i, n) t[b[i]] = i;     // t = 0,0,1,2,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
  lp(i, n)
  {
    if (bs[i])
      continue;
    int cur = i;
    int m = max_v;
    int S = 0;
    int an = 0;

    while (true) {
      bs[cur] = true;
      an++;
      int v = a[cur];
      m = min(m, v);
      S += v;
      cur = t[v];
      if (bs[cur])
        break;
    }
    // Σwi + (n-2) * min(w1) or Σwi +  min(w1) + (n-1) * x
    ans += min(S + (an - 2) * m, m + S + (an + 1) * s);
  }
  return ans;
}

template <typename T> auto in() -> T
{
  int inp;
  cin >> inp;
  return inp;
}

auto main() -> int
{
  vector<int> a;
  int i, n, s;

  cin >> n;
  s = max_v;

  lp(i, n)
  {
    a.push_back(in<int>());
    s = min(s, a.back()); // most likely  s == 1
  }

  int ans = solve(a, n, s);
  cout << ans << endl;

  return 0;
}