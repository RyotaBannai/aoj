#include <array>
#include <iostream>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;

static const int N = 100;

auto main() -> int
{
  array<array<int, N + 1>, N + 1> mat{};
  int i, j, n, u, v, k;
  cin >> n;

  lp(i, n)
  {
    cin >> u >> k;
    --u; // 0 オリジンなので u > 0
    lp(j, k)
    {
      cin >> v;
      mat[u][--v] = 1; // 0 オリジンなので v > 0
    }
  }

  lp(i, n)
  {
    lp(j, n)
    {
      if (j)
        cout << " ";
      cout << mat[i][j];
    }
    cout << endl;
  }
  return 0;
}