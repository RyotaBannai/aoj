#include <algorithm>
#include <iostream>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
#define lps(i, j, n) for (int i = j; i < n; i++)
using namespace std;

static const int MAX = 100000;
int n;
int a[MAX + 1], l[MAX];
auto lis() -> int
{
  l[0] = a[0];
  int length = 1; // i 番目の要素までを使った最長増加部分列の長さを表す整数
  lps(i, 1, n)
  {
    if (l[length - 1] < a[i])
      // 今回の要素が一番後ろの要素より大きい場合は一番後ろに追加
      l[length++] = a[i];
    else
      // そうで無い場合は、0 <= i <= length - 1
      // の範囲で今回分（a[i]）以上（<=）の位置にある要素と入れ替える
      // = 同じ、または小さくなる
      *lower_bound(l, l + length, a[i]) = a[i];
  }
  return length;
}

auto main() -> int
{
  cin >> n;
  lp(i, n) cin >> a[i];
  cout << lis() << endl;
}