#include <iostream>
#include <stack>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
#define lps(i, j, n) for (int i = j; i < n; i++)
using namespace std;

static const int MAX = 1400;
int tiles[MAX][MAX], T[MAX][MAX];
int H, W;

struct Rect {
  int height, pos;
};

auto largest_rect(int row) -> int
{
  stack<Rect> s;
  int maxv = 0;
  auto buffer = T[row]; // 今回分の行をセット
  buffer[W] = 0; // stack に溜まった計算予定の面積を精算するために末尾に最小値を追加

  lp(i, W + 1) // 水平方向へ走査
  {
    Rect rect;
    rect.height = buffer[i];
    rect.pos = i;
    if (s.empty())
      s.push(rect);
    else {
      if (s.top().height < rect.height)
        s.push(rect);
      else if (s.top().height > rect.height) {
        int target = i;
        /*
        注目してるヒストグラムの高さが、s.top よりも低い時、s.top
        の高さで長方形を作成することはできない、ということ.
        注目してるヒストグラムの高さより大きい、左端のヒストグラムまで取り出すしつつ、注目してる
        index からその取り出したヒストグラムまでの差分と高さで面積を求める
        */
        while (!s.empty() && s.top().height >= rect.height) {
          Rect pre = s.top();
          s.pop();
          int area = pre.height * (i - pre.pos);
          maxv = max(maxv, area);
          target = pre.pos;
        }
        rect.pos = target;
        s.push(rect);
      }
    }
  }
  return maxv;
}

auto solve() -> int
{
  int maxv = 0;
  lp(i, H) maxv = max(maxv, largest_rect(i));
  return maxv;
}

void histgram()
{
  lp(j, W) T[0][j] = tiles[0][j] ? 0 : 1;
  lps(i, 1, H) lp(j, W) T[i][j] = tiles[i][j] ? 0 : T[i - 1][j] + 1;
}

auto main() -> int
{
  cin >> H >> W;
  lp(i, H) lp(j, W) cin >> tiles[i][j];
  histgram();
  cout << solve() << endl;
}