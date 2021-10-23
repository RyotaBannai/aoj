#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#define lp(i, n) for (int i = 0; i < n; i++)
#define lps(i, j, n) for (int i = j; i < n; i++)
using namespace std;
static const int N = 4;
static const int N2 = 16;
static const int LIMIT = 100;
static const int dx[4] = {1, 0, -1, 0};
static const int dy[4] = {0, -1, 0, 1};
static const char dir[4] = {'r', 'u', 'l', 'd'};

struct Puzzle {
  int f[N2], space, MD;
};

Puzzle state;
int limit; // 深さの制限
int path[LIMIT];
/*
0123123423453456
1012212332344345
2101321243235434
3210432154326543
1234012312342345
2123101221233234
3212210132124323
4321321043215432
2345123401231234
3234212310122123
4323321221013212
5432432132104321
3456234512340123
4345323421231012
5434432332122101
6543543243213210
*/
int MDT[N2][N2];

auto get_all_md(Puzzle p) -> int
{
  int sum = 0;
  lp(i, N2)
  {
    if (p.f[i] == N2) // スペースは必然的に配置されるため考慮しない
      continue;
    sum += MDT[i][p.f[i] - 1];
  }
  return sum;
}

auto is_solved(Puzzle p) -> bool
{
  lp(i, N2) if (state.f[i] != i + 1) return false;
  return true;
}

auto dfs(int depth, int prev) -> bool
{
  if (state.MD == 0)
    return true;
  if (depth + state.MD > limit)
    return false;

  int sx = state.space % N;
  int sy = state.space / N;
  Puzzle tmp;

  lp(r, 4)
  {
    int tx = sx + dx[r];
    int ty = sy + dy[r];
    if (ty < 0 || tx < 0 || ty >= N || tx >= N)
      continue;
    // 前回と同じ位置に戻さないように調整. i.g. 左 → 右, 上 → 下
    if (max(prev, r) - min(prev, r) == 2)
      continue;
    tmp = state;
    int idxt = ty * N + tx; // スワップ対象
    int idxs = sy * N + sx; // スペース
    // 本来移動に必要だった対象の MD がなくなるためその分を引く
    state.MD -= MDT[idxt][state.f[idxt] - 1];
    // 次に、移動した対象が新しい位置から本来あるべき位置までに必要になる MD を加える
    state.MD += MDT[idxs][state.f[idxt] - 1];
    swap(state.f[idxt], state.f[idxs]);
    state.space = idxt;
    // 移動に成功した場合に、再帰的に最上階の関数呼び出しへ戻りながら、利用してきたパスを path
    // に追加
    if (dfs(depth + 1, r)) {
      path[depth] = r;
      return true;
    }
    state = tmp; // 失敗したら今回の状態に戻す
  }
  return false;
}

auto iterative_deepening(Puzzle in) -> string
{
  in.MD = get_all_md(in); // 初期状態のマンハッタン距離
  for (limit = in.MD; limit <= LIMIT; limit++) {
    state = in;
    if (dfs(0, -100)) {
      string ans = "";
      // lp ごとに limit が増えていくため、特に初期化せずに上書きして利用
      lp(i, limit) ans += dir[path[i]];
      return ans;
    }
  }

  return "unsolvable";
}

auto main() -> int
{
  lp(i, N2) lp(j, N2) MDT[i][j] = abs(i / N - j / N) + abs(i % N - j % N);
  Puzzle in;
  lp(i, N2)
  {
    cin >> in.f[i];
    if (in.f[i] == 0) {
      in.f[i] = N2;
      in.space = i;
    }
  }
  cout << iterative_deepening(in).size() << endl;
}