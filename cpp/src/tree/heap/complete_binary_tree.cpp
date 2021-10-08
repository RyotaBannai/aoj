#include <array>
#include <iostream>
#define lps(i, j, n) for (int i = j; i < n; i++)
using namespace std;

const int MAX = 100000;

auto parent(int i) -> int { return i / 2; }
auto left(int i) -> int { return 2 * i; }
auto right(int i) -> int { return 2 * i + 1; }

template <typename T> auto in() -> T
{
  T inp;
  cin >> inp;
  return inp;
}

auto main() -> int
{
  int i, n;
  array<int, MAX + 1> arr; // 1 オリジンのため

  cin >> n;
  lps(i, 1, n + 1) arr[i] = in<int>();
  lps(i, 1, n + 1)
  {
    cout << "node " << i << ": key = " << arr[i] << ", ";
    if (parent(i) >= 1)
      // root 以外を表示する 1/2 -> 0 index
      cout << "parent key = " << arr[parent(i)] << ", ";
    if (left(i) <= n)
      cout << "left key = " << arr[left(i)] << ", ";
    if (right(i) <= n)
      cout << "right key = " << arr[right(i)] << ", ";

    cout << endl;
  }

  return 0;
}