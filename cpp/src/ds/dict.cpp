/*
Linear Probing で利用

Open address 法 - ダブルハッシュ: ハッシュ値が衝突する際に二つ目のハッシュ関数を使う.
i:= 衝突が発生して次のハッシュ値を計算した回数
h(k,0), h(k,1), h(k,2),...

*/
#include <iostream>
#include <string>
using namespace std;
using ll = long long;

constexpr int M = 1046527;
constexpr int NIL = -1;
string map[M];

auto h1(ll key) -> int { return key % M; }
/*
h2(key) と map のサイズ（M）が互いに素でないといけない.
M を素数にして、h2(key) を M より小さい値に設定することで回避することができる.
*/
auto h2(ll key) -> int { return 1 + (key % (M - 1)); }
auto h(ll key, int i) -> int { return (h1(key) + i * h2(key)) % M; }

// auto getChar(char c) -> int
// {
//   if (c == 'A')
//     return 1;
//   else if (c == 'C')
//     return 2;
//   else if (c == 'G')
//     return 3;
//   else if (c == 'T')
//     return 4;
//   else
//     return 0;
// }

auto getChar(char c) -> int
{
  int n = c - 'A';
  return n;
}

auto getKey(string str) -> long long
// 文字列から数値へ変換し key を生成
{
  long long sum = 0, p = 1;
  for (const char &c : str) {
    sum += p * getChar(c);
    p *= 5;
  }
  return sum;
}

auto insert(string s) -> int
// insert sucessfully = j, where string is inserted,
// already inserted = 0
{
  ll key = getKey(s);
  for (int i = 0;; i++) {
    int j = h(key, i);
    if (map[j] == s)
      return 0;
    else if (map[j] == "") {
      map[j] = s;
      return j;
    }
  }
}

auto find(string s) -> int
// found = 1, not found = 0
{
  ll key = getKey(s);
  for (int i = 0;; i++) {
    int j = h(key, i);
    if (map[j] == s)
      return 1;
    else if (map[j] == "" || i >= M)
      return 0;
  }
}

auto main() -> int
{
  int N;
  string com, str;
  fill(begin(map), end(map), "");
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> com >> str;
    if (com[0] == 'i')
      insert(str);
    else
      cout << (find(str) ? "yes" : "no") << endl;
  }
}