#include <iostream>
#include <map>
#include <queue>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;
static const int N = 4;
static const int N2 = 16;
static const int LIMIT = 100;
static const int dx[4] = {1, 0, -1, 0};
static const int dy[4] = {0, -1, 0, 1};
static const char dir[4] = {'r', 'u', 'l', 'd'};
int MDT[N2][N2];

struct Puzzle {
  int f[N2], space, MD, cost;
  auto operator<(const Puzzle &p) const -> bool
  {
    lp(i, N2)
    {
      if (f[i] == p.f[i])
        continue;
      return f[i] < p.f[i];
    }
    return false;
  }
};

struct State {
  Puzzle puzzle;
  int estimated; // priority queue の優先度のため設定
  auto operator<(const State &s) const -> bool
  /*
  デフォルトは降順（std::less<T>）-> 昇順に設定
  estimated が最小の state が pop されるように設定
  <https://cpprefjp.github.io/reference/queue/priority_queue.html>
  */
  {
    return estimated > s.estimated;
  }
};

auto get_all_md(Puzzle p) -> int
{
  int sum = 0;
  lp(i, N2)
  {
    if (p.f[i] == N2)
      continue;
    sum += MDT[i][p.f[i] - 1];
  }
  return sum;
}

auto astar(Puzzle s) -> int
{
  priority_queue<State> pq;
  s.MD = get_all_md(s);
  s.cost = 0;
  map<Puzzle, bool> V;
  Puzzle u, v;
  State initial;
  initial.puzzle = s;
  initial.estimated = get_all_md(s);
  pq.push(initial);

  while (!pq.empty()) {
    State st = pq.top();
    pq.pop();
    u = st.puzzle;
    if (u.MD == 0)
      return u.cost;
    V[u] = true;

    int sx = u.space % N;
    int sy = u.space / N;

    lp(r, 4)
    {
      int tx = sx + dx[r];
      int ty = sy + dy[r];
      if (ty < 0 || tx < 0 || ty >= N || tx >= N)
        continue;

      v = u;
      int idxt = ty * N + tx;
      int idxs = sy * N + sx;
      v.MD -= MDT[idxt][v.f[idxt] - 1];
      v.MD += MDT[idxs][v.f[idxt] - 1];
      swap(v.f[idxt], v.f[idxs]);
      v.space = idxt;

      if (!V[v]) {
        // 開始地点から現在位置までのコスト
        // := queue で処理され、新しい State が作られてるごとに +1 する
        v.cost++;
        State new_s;
        new_s.puzzle = v;
        new_s.estimated = v.cost + v.MD;
        pq.push(new_s);
      }
    }
  }

  return -1;
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
  cout << astar(in) << endl;
}