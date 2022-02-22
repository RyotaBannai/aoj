/*
最長共通部分列
https://leetcode.com/problems/longest-common-subsequence/

参考
http://www.cs.t-kougei.ac.jp/SSys/LCS.htm

・共通部分を一つ見つけたときに +1
・`共通部分を比較する時の index はあくまで文字列であって mat ではない`
・それ以外は同じ数値を引き継ぐ

・列単位で見るため、先に同じ文字を発見して +1 しても、同じ列で同じ 2
文字目が発見されてもその際は、上を見るのではなく、斜め上を見るため二重に加算することはない.　→
つまり同じ文字のベアが２つあれば必ず別々にマッチングしてそれぞれ +1 ずつされる.
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
  string S, T; // abcde, ace
  cin >> S >> T;

  array<array<int, MAX + 1>, MAX + 1> mat{}; // 全要素を 0 で初期化

  // 最長一致の行列を作成
  for (int s = 0; s <= S.size(); ++s) {
    for (int t = 0; t <= T.size(); ++t) { // 内側のループで列方向に進行
      if (S[s] == T[t]) {
        mat[t + 1][s + 1] = mat[t][s] + 1;
      }
      else {
        mat[t + 1][s + 1] = max(mat[t + 1][s], mat[t][s + 1]);
      }
    }
  }

  // LCS がうまくいかない. test case 1 で c を2回カウント
  string ans1 = "";
  for (int t = 1; t <= T.size(); ++t) {
    for (int s = 1; s <= S.size(); ++s) {
      /*
       上左の数値が同じで、かつターゲットよりちょうど一つ小さい = 行で初めて一致した文字
       length の判定で、すでにすぎた文字を拾わないよう調整
      */
      if (mat[t][s - 1] == mat[t - 1][s] && mat[t][s - 1] == mat[t][s] - 1) {
        if (mat[t][s] > ans1.length()) {
          ans1 += S[s - 1];
        }
      }
    }
  }

  // string ans2 = "";
  // for (int s = 1; s <= S.size(); ++s) {
  //   for (int t = 1; t <= T.size(); ++t) {
  //     if (mat[t][s - 1] == mat[t - 1][s] && mat[t][s - 1] == mat[t][s] - 1) {
  //       if (mat[t][s] > ans2.length()) {
  //         ans2 += T[t - 1];
  //       }
  //     }
  //   }
  // }

  cout << ans1 << endl;
  cout << ans2 << endl;

  // debug
  // cout << std::right << std::setw(10) << "debug:" << endl;
  // cout << std::right << std::setw(11) << " ";

  // for (auto c : S) {
  //   cout << std::right << std::setw(10) << c;
  // }
  // cout << endl;

  // for (int t = 0; t <= T.size(); ++t) {
  //   cout << std::right << (t == 0 ? " " : string(1, T[t - 1]));
  //   for (int s = 0; s <= S.size(); ++s) {
  //     cout << std::right << std::setw(10) << mat[t][s];
  //   }
  //   cout << endl;
  // }
}