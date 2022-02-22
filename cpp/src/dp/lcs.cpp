/*
最長共通部分列
https://leetcode.com/problems/longest-common-subsequence/

参考
http://www.cs.t-kougei.ac.jp/SSys/LCS.htm

TODO: 同じ文字が来たときの挙動確認
*/

#include <array>
#include <iomanip> // std::setw(int), std::setfill(char)
#include <ios>     // std::left, std::right
#include <iostream>
#include <string>
using namespace std;
const int MAX = 1000;

auto main() -> int
{
  string s1, s2; // abcde, ace
  cin >> s1 >> s2;

  array<array<int, MAX + 1>, MAX + 1> mat{}; // 全要素を 0 で初期化

  string ans = "";
  for (int i = 0; i <= s1.size(); ++i) {
    for (int j = 0; j <= s2.size(); ++j)
    // 共通部分を一つ見つけたときに斜め左上の数値をベースに +1 する.
    // それ以外は同じ数値を引き継ぐ
    {
      if (s1[i] == s2[j]) {
        mat[i + 1][j + 1] = mat[i][j] + 1;
        ans += s1[i];
      }
      else {
        mat[i + 1][j + 1] = max(mat[i + 1][j], mat[i][j + 1]);
      }
    }
  }

  // debug
  // for (int i = 0; i <= s2.size(); ++i) {
  //   for (int a = 0; a <= s1.size(); ++a) {
  //     cout << std::right << std::setw(10) << mat[a][i];
  //   }
  //   cout << endl;
  // }

  // debug
  // cout << std::right << std::setw(10) << "debug" << endl;
  // cout << std::right << std::setw(10) << " ";

  // for (auto x : s1) {
  //   cout << std::right << std::setw(10) << x;
  // }
  // cout << endl;

  // for (int i = 0; i <= s2.size(); ++i) {
  //   cout << std::right << string(1, s2[i]);
  //   for (int a = 0; a <= s1.size(); ++a) {
  //     cout << std::right << std::setw(10) << mat[a][i];
  //   }
  //   cout << endl;
  // }

  cout << ans << endl;
}