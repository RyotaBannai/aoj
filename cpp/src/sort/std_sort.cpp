#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;

void print_vector_int(const vector<int> v)
{
  for (auto x = v.begin(); x != v.end(); ++x)
    cout << *x << (x != --v.end() ? ',' : ' ');
  cout << endl;
}

// T::iterator の前の typename は iterator が型であって、値でないことをコンパイラに知らせる.
template <typename T> using Iterator = typename T::iterator;

// find all pointer to value v in container C, such as `string` and return a vector of all pointers
template <typename C, typename V> auto find_all(C &c, V v) -> vector<Iterator<C>>
// (112)
{
  vector<Iterator<C>> res;
  for (auto p = c.begin(); p != c.end(); p++)
    if (*p == v)
      res.push_back(p);
  return res;
}

void swap(vector<int> &v, int i, int j)
{
  int t = v[i];
  v[i] = v[j];
  v[j] = t;
}

void expr()
{
  vector<int> vec{10, 20, 30};
  swap(vec, 0, 2);
  print_vector_int(vec);
}

template <typename T> auto in() -> T
{
  T inp;
  cin >> inp;
  return inp;
}

namespace Estd {
  using namespace std;
  template <typename C> void sort(C &c) { sort(c.begin(), c.end()); }
  template <typename C, typename Pred> void sort(C &c, Pred p) { sort(c.begin(), c.end(), p); }
}

void use_std_sort()
/*
p173
in:
5
5 3 4 1 2
out:
1 2 3 4 5
*/
{
  int n, i;
  vector<int> v;
  cin >> n;

  lp(i, n) v.push_back(in<int>());
  Estd::sort(v);

  for (auto x : v)
    cout << x << " ";

  cout << endl;
}

auto main() -> int
{
  // expr();
  use_std_sort();
  return 0;
}