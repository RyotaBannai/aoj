#include <algorithm>
#include <iostream>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;

int pos, n;
vector<int> preo, ino, posto;

struct Node {
  int parent, left, right;
};

void rec(int l, int r)
/*
・preo を rec を呼び出すたびに index を増やし root を取り出す.
- 再帰的に呼ばれる過程で増えるのも問題ない
- root を取り出した時にすでに leaf だったりすると (l >= r) の条件で再帰が完了. 前の再帰に遡り pb
で追加.
・ino の root の位置をもと特定し sub tree ごとに node 群を分割

vector<int> v = {1,2,3}
distance(v.begin(), v.end()) = 3
distance(v.begin(), find(v.begin, v.end(), 3)) = 2
*/
{
  if (l >= r)
    return;
  int root = preo[pos++];
  int m = distance(ino.begin(), find(ino.begin(), ino.end(), root));
  // cout << l << " " << m << " " << r << " root " << root << " " << endl;
  rec(l, m);
  rec(m + 1, r);
  posto.push_back(root);
}

void solve()
{
  pos = 0;
  rec(0, preo.size());
  lp(i, n)
  {
    if (i)
      cout << " ";
    cout << posto[i];
  }
  cout << endl;
}

template <typename T> auto in() -> T
{
  T inp;
  cin >> inp;
  return inp;
}

auto main() -> int
{
  int i;
  cin >> n;

  lp(i, n) preo.push_back(in<int>());
  lp(i, n) ino.push_back(in<int>());

  solve();

  return 0;
}