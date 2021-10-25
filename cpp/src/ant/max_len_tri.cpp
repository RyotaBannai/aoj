#include <cmath>
#include <iostream>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
#define lps(i, j, n) for (int i = j; i < n; i++)
using namespace std;

int n;
vector<int> a;
void solve()
{
  int maxv = 0;
  // 組み合わせで重複しないよう i < j < k とする
  lp(i, n) lps(j, i + 1, n) lps(k, j + 1, n)
  {
    int len = a[i] + a[j] + a[k];
    int ma = max(a[i], max(a[j], a[k]));
    if (len - ma > ma) {
      maxv = max(len, maxv);
    }
  }
  cout << maxv << endl;
}

auto main() -> int
{
  cin >> n;
  a.reserve(n);
  lp(i, n) cin >> a[i];
  solve();
}