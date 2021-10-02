#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
#define lps(i, j, n) for (int i = j; i < n; i++)
using namespace std;

const int v_max = 10000;

template <class T> void print_vector_int(const vector<T> v)
{
  for (auto x = v.begin(); x != v.end(); ++x)
    cout << *x << (x != --v.end() ? ',' : ' ');
  cout << endl;
}

auto main() -> int
{
  int n, i, j;
  scanf("%d", &n);
  vector<int> vec_c(v_max);
  vector<unsigned short> vec_a(n + 1), vec_b(n + 1);
  std::fill(vec_c.begin(), vec_c.end(), 0);

  lp(i, n)
  {
    scanf("%hu", &vec_a[i + 1]);
    vec_c[vec_a[i + 1]]++;
  }
  // print_vector_int(vec_a); // 0,2,5,1,3,2,3
  // print_vector_int(vec_c); // 1,1,2,2,0,1,0,0,...

  lps(i, 1, v_max + 1) vec_c[i] += vec_c[i - 1];
  // print_vector_int(vec_c); // 1,2,4,6,6,7,...
  lps(j, 1, n + 1)
  {
    int num = vec_a[j];
    vec_b[vec_c[num]] = num;
    vec_c[num]--;
  }
  lps(i, 1, n + 1)
  {
    if (i > 1)
      printf(" ");
    printf("%d", vec_b[i]);
  }

  printf("\n");

  return 0;
}