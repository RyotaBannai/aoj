#include <iostream>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)

using namespace std;
using ll = long long;

const int sentinel = 2000000000;
const int m = 200000;
vector<int> vl(m / 2 + 2), vr(m / 2 + 2);

auto merge(vector<int> &v, const int l, const int mid, const int r) -> ll
{
  int i, j, k;
  int cnt = 0;
  int n1 = mid - l;
  int n2 = r - mid;

  for (i = 0; i < n1; i++)
    vl[i] = v[l + i];
  for (j = 0; j < n2; j++)
    vr[j] = v[mid + j];

  vl[n1] = vr[n2] = sentinel;
  i = j = 0;

  for (k = l; k < r; k++) {
    if (vl[i] <= vr[j])
      v[k] = vl[i++];
    else {
      v[k] = vr[j++];
      cnt += n1 - i; // 反点数を計算. Or `= mid + j - k - 1`
    }
  }

  return cnt;
}

auto msort(vector<int> &v, int l, int r) -> ll
{
  int mid;
  ll cnt1, cnt2, cnt3;

  if (l + 1 < r) {
    mid = (l + r) / 2;
    cnt1 = msort(v, l, mid);
    cnt2 = msort(v, mid, r);
    cnt3 = merge(v, l, mid, r);
    return cnt1 + cnt2 + cnt3;
  }
  else
    return 0;
}

auto main() -> int
{
  int n, i;
  vector<int> v(m);

  cin >> n;
  lp(i, n) scanf("%d", &v[i]);
  ll ans = msort(v, 0, n);
  cout << ans << endl;

  return 0;
}
