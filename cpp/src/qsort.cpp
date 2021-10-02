#include <array>
#include <cstdio>
#include <iostream>
#include <vector>
#define SENTINEL 2000000000;

using namespace std;

struct Card {
  char suit;
  int value;
};

void print_vector_int(const vector<Card> v)
{
  for (auto x = v.begin(); x != v.end(); ++x)
    cout << x->suit << ' ' << x->value << (x != --v.end() ? ',' : ' ');
  cout << endl;
}

int m = 6;
vector<Card> vec_l(m / 2 + 2), vec_r(m / 2 + 2);

void merge(vector<Card> &vec, const int l, const int mid, const int r)
{
  int i, j, k;
  int n1 = mid - l;
  int n2 = r - mid;

  for (i = 0; i < n1; i++)
    vec_l[i] = vec[l + 1];
  for (j = 0; j < n2; j++)
    vec_r[j] = vec[mid + 1];

  // vec_l, vec_r の末尾にどの数値よりも大きな番兵を置くことで簡略化する
  // r-l 回だけループするようにすれば、実際に番兵どうしが比較されることも、i, j が n1, n2
  // を超えることもない.
  vec_l[n1].value = vec_r[n2].value = SENTINEL;
  i = j = 0;

  for (k = l; k < r; k++) {
    if (vec_l[i].value <= vec_r[j].value)
      vec[k] = vec_l[i++];
    else
      vec[k] = vec_r[j++];
  }
}

void msort(vector<Card> &vec, int l, int r)
{
  int mid;
  if (l + 1 < r) {
    mid = (l + r) / 2;
    msort(vec, l, mid);
    msort(vec, mid, r);
    merge(vec, l, mid, r);
  }
}

template <class T> void swap_vec_elem(vector<T> &v, int i, int j)
{
  T t = v[i];
  v[i] = v[j];
  v[j] = t;
}

auto partition(vector<Card> &vec, int p, int r) -> int
{
  int i, j;
  struct Card t, x;
  x = vec[r];
  i = p - 1;

  for (j = p; j < r; j++) {
    if (vec[j].value <= x.value) {
      i++;
      swap_vec_elem(vec, i, j);
    }
  }

  swap_vec_elem(vec, i + 1, r);
  return i + 1;
}

void qsort(vector<Card> &vec, int p, int r)
{
  int q;
  if (p < r) { // 要素数が二個にまで続けられる
    q = partition(vec, p, r);
    qsort(vec, p, q - 1);
    qsort(vec, q + 1, r);
  }
}

auto main() -> int
{
  int n, i, v;
  scanf("%d", &n);
  // array<char, 10> S; // use this instead of C-style arrays
  char S[10];
  vector<Card> vec_a(n), vec_b(n);
  int stable = 1;

  for (i = 0; i < n; i++) {
    scanf("%s %d", S, &v);
    vec_a[i].suit = vec_b[i].suit = S[0];
    vec_a[i].value = vec_b[i].value = v;
  }

  qsort(vec_a, 0, n - 1);
  msort(vec_b, 0, n);

  print_vector_int(vec_a);
  print_vector_int(vec_b);

  // for (i = 0; i < n; i++) {
  //   if (vec_a[i].suit != vec_b[i].suit)
  //     stable = 0;
  // }

  // if (stable == 1)
  //   printf("Stable\n");
  // else
  //   printf("Not stable\n");

  // for (auto x : vec_b) {
  //   printf("%c %d\n", x.suit, x.value);
  // }

  return 0;
}