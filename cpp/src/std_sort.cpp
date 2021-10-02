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

template <class T> auto in() -> T
{
  int inp;
  cin >> inp;
  return inp;
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
  sort(v.begin(), v.end());

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