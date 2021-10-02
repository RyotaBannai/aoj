#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

void swap_vec_elem(vector<int> &v, int i, int j)
{
  int t = v[i];
  v[i] = v[j];
  v[j] = t;
}

auto partition(vector<int> &vec, int p, int r) -> int
{
  int x, i, j, t;
  x = vec[r];
  i = p - 1;

  for (j = p; j < r; j++) {
    if (vec[j] <= x) {
      i++;
      swap_vec_elem(vec, i, j);
    }
  }

  swap_vec_elem(vec, i + 1, r); // base の数より一つ大きい場所と base を swap
  return i + 1;
}

auto main() -> int
{
  int n, i, q;
  scanf("%d", &n);
  vector<int> vec(n);

  for (i = 0; i < n; i++)
    scanf("%d", &vec[i]);

  q = partition(vec, 0, n - 1);

  for (i = 0; i < n; i++) {
    if (i)
      printf(" ");

    // base の数より一つ大きい場所を [] でラップ
    if (i == q)
      printf("[");
    printf("%d", vec[i]);
    if (i == q)
      printf("]");
  }

  printf("\n");

  return 0;
}