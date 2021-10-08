#include <array>
#include <iostream>
#include <string>
using namespace std;

const int MAX = 2000000;
const long long INF = (1 << 30);
int n;
array<int, MAX + 1> arr;

auto parent(int i) -> int { return i / 2; }
auto left(int i) -> int { return 2 * i; }
auto right(int i) -> int { return 2 * i + 1; }

void max_heapify(int i)
{
  int l = left(i);
  int r = right(i);
  int largest = l <= n && arr[l] > arr[i] ? l : i;
  largest = r <= n && arr[r] > arr[largest] ? r : largest;

  if (largest != i) {
    swap(arr[i], arr[largest]);
    max_heapify(largest);
  }
}

auto extract() -> int
{
  if (n < 1)
    return -INF;
  int root = arr[1];
  // 一番最後の要素を先頭に入れてそれを要素を適切な場所に下げていくことで、
  // max heap になることを保証
  arr[1] = arr[n--];
  max_heapify(1);

  return root;
}

void increase_key(int n, int key)
{
  // parent と比較しならがらより大きければ swap
  // 自分より大きい値が parent に来るまで繰り返す
  while (n > 1 && arr[parent(n)] < arr[n]) {
    swap(arr[n], arr[parent(n)]);
    n = parent(n);
  }
}

void insert(int key)
{
  n++;
  arr[n] = -INF > key ? -INF : key; // -INF で設定した下限よりも大きいことを保証
  increase_key(n, key);
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
  string com;
  while (true) {
    cin >> com;
    if (com[0] == 'e' && com[1] == 'n')
      break;
    if (com[0] == 'i')
      insert(in<int>());
    else
      printf("%d\n", extract());
  }

  return 0;
}