#include <algorithm>
#include <iostream>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
#define lps(i, j, n) for (int i = j; i < n; i++)
using namespace std;

static const int MAX = 1400;
int tiles[MAX][MAX];
int H, W;

auto largest_square() -> int
{
  // タイルが一つの場合に、その一つが綺麗か汚れているかを確認する必要があるため都度チェック
  int squares[MAX][MAX], maxw = 0;
  lp(i, H) maxw = (squares[i][0] = tiles[i][0] ? 0 : 1) ? 1 : maxw;
  lp(j, W) maxw = (squares[0][j] = tiles[0][j] ? 0 : 1) ? 1 : maxw;

  lps(i, 1, H) lps(j, 1, W)
  {
    if (tiles[i][j]) // 1 := 汚れている, 0 := 綺麗なまま
      squares[i][j] = 0;
    else {
      squares[i][j] = min(squares[i - 1][j - 1], min(squares[i - 1][j], squares[i][j - 1])) + 1;
      maxw = max(maxw, squares[i][j]);
    }
  }
  return maxw * maxw;
}

auto main() -> int
{
  cin >> H >> W;
  lp(i, H) lp(j, W) cin >> tiles[i][j];
  cout << largest_square() << endl;
}