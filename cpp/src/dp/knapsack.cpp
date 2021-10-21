#include <algorithm>
#include <iostream>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
#define lps(i, j, n) for (int i = j; i < n; i++)
using namespace std;

static const int NMAX = 105;
static const int WMAX = 10005;
static const int DIAGONAL = 1;
static const int TOP = 0;
/*
N := 品物数
W := 求めたいナップザックの大きさ
*/
int N, W;

struct Item {
  int v, w;
  Item(int v = 0, int w = 0) : v(v), w(w) {}
};

/*
c := i 個までの品物を考慮して大きさ w のナップザックに入れる場合の価値の合計の最大値 c[i][w]
とする配列
g := 品物の選択状況を記録（diagonal | top）
　diagonal := 今回分の重さ w を差し引いた重さの最大値を左斜めから取得
　top := 今回分を使用しても最大値にならないため、前回までの品物を使った最大値をそのまま真上から取得
*/
int c[NMAX + 1][WMAX + 1], g[NMAX + 1][WMAX + 1];
vector<Item> items = {Item()};

void compute(int &maxv, vector<int> &selection)
{
  lp(w, W + 1) c[0][w] = 0, g[0][w] = DIAGONAL; // 0 行、列を初期化
  lps(i, 1, N + 1) g[i][0] = 0;
  lps(i, 1, N + 1)
  {
    int prev_i = i - 1;
    Item item = items[i];
    lps(w, 1, W + 1)
    {
      int new_maxv;
      c[i][w] = c[prev_i][w], g[i][w] = TOP; // 今回分を計算前に初期化
      if (item.w > w)
        continue;
      if ((new_maxv = item.v + c[prev_i][w - item.w]) > c[prev_i][w]) {
        c[i][w] = new_maxv, g[i][w] = DIAGONAL; // 最大価値を更新したときに今回分を update
      }
    }
  }
  maxv = c[N][W];

  // 最大値を取得するまでに通ってきた path を逆順で品物を拾いながら 0 へ戻る
  // こうすることで最大価値を選択する過程を出力することができる
  selection.clear();
  for (int i = N, w = W; i >= 1; i--)
    if (g[i][w] == DIAGONAL)
      selection.push_back(i), w -= items[i].w;

  reverse(selection.begin(), selection.end());
}

auto main() -> int
{
  int v, w, maxv;
  vector<int> selection;
  cin >> N >> W;
  lp(i, N) cin >> v >> w, items.emplace_back(v, w);
  compute(maxv, selection);

  cout << maxv << endl;
}