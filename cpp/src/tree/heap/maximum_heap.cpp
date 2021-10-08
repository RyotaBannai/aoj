#include <array>
#include <iostream>
#define lps(i, j, n) for (int i = j; i < n; i++)
using namespace std;

const int MAX = 100000;
int n;                   // 要素数
array<int, MAX + 1> arr; // heap

auto left(int i) -> int { return 2 * i; }
auto right(int i) -> int { return 2 * i + 1; }

void max_heapify(int i)
{
  int l, r, largest;
  l = left(i);
  r = right(i);

  // 要素数オーバーチェックと要素の最小比較を左右の children と自分自身で行う.
  largest = l <= n && arr[l] > arr[i] ? l : i;
  largest = r <= n && arr[r] > arr[largest] ? r : largest;

  if (largest != i) {
    swap(arr[i], arr[largest]);
    // largest はすでにスワップされているため、largest ではなかった i を
    // largest の children と再度比較（再帰的）
    max_heapify(largest);
  }
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

  lps(i, 1, n + 1) arr[i] = in<int>();
  for (int i = n / 2; i >= 1; i--)
    max_heapify(i);
  lps(i, 1, n + 1) cout << " " << arr[i];
  cout << endl;

  return 0;
}