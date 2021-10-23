#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;
static const int N = 3;
static const int N2 = 9;

struct Puzzle {
  int f[N2], space;
  string path;

  auto operator<(const Puzzle &p) const -> bool
  // ハッシュマップのキーの計算用
  {
    lp(i, N2)
    {
      if (f[i] == p.f[i])
        continue;
      return f[i] > p.f[i];
    }
    return false;
  }
};
// スペースの周りの４方向のパターンを反時計回りに定義
static const int dy[4] = {-1, 0, 1, 0};
static const int dx[4] = {0, -1, 0, 1};
// 交換対象から見たスペースの相対的な位置
static const char dir[4] = {'u', 'l', 'd', 'r'};

auto is_target(Puzzle p) -> bool
{
  lp(i, N2) if (p.f[i] != (i + 1)) return false;
  return true;
}

auto bfs(Puzzle s) -> string
{
  queue<Puzzle> q;
  map<Puzzle, bool> V;
  Puzzle u, v;
  s.path = "";
  q.push(s);
  V[s] = true;

  while (!q.empty()) {
    u = q.front(), q.pop();
    if (is_target(u))
      return u.path;
    int sy = u.space / N; // 縦方向の位置
    int sx = u.space % N; // 横方向の位置

    lp(r, 4)
    {
      int ty = sy + dy[r];
      int tx = sx + dx[r];
      if (ty < 0 || tx < 0 || ty >= N || tx >= N) //パズルの NxN 範囲内の操作かどうかチェック
        continue;
      v = u;
      swap(v.f[u.space], v.f[ty * N + tx]);
      v.space = ty * N + tx;
      if (!V[v]) {
        V[v] = true;
        v.path += dir[r];
        q.push(v);
      }
    }
  }
  return "unsolvable";
}

auto main() -> int
{
  Puzzle in;
  lp(i, N2) // NxN のパズルのマスを一次元配列として受け付ける
  {
    cin >> in.f[i];
    if (in.f[i] == 0) {
      in.f[i] = N2; // 0 は最後に配置したいため一番大きい数値をセット
      in.space = i;
    }
  }
  cout << bfs(in).size() << endl;
}