#include <iostream>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;

// 素数判定
// 他にもエラストテネスの篩によっても O(N log log N) のアルゴリズムで求めることができる
auto is_prim(int x) -> int
{
  int i;
  if (x < 2)
    return 0;
  else if (x == 2)
    return 1;
  else if (x % 2 == 0)
    return 0;
  else
    /*
    「合成数 x は p <= √x を満たす素因子 p を持つ」という性質を利用して素数判定を行う
    例えば、31 を判定するときには 2 <= p <= 5.?? (√31) の数で割り切れるかどうか確認する
    もし 31 が合成数であるため、√31 <= p <= 30 の間に 31 を割り切れる数が存在するのであれば、
    すでに調べた 2 <= p <= 5.?? の数に 31 を割り切れる数が必ず存在するため、5.??
    を超える数を調べる必要はない
    */
    for (i = 3; i * i <= x; i += 2)
      if (x % i == 0)
        return 0;

  return 1;
}

auto main() -> int
{
  int n, x, i;
  int cnt = 0;
  cin >> n;
  lp(i, n)
  {
    cin >> x;
    if (is_prim(x))
      cnt++;
  }
  cout << cnt << endl;
}