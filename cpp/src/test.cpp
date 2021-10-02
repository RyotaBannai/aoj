#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

void print_vector_int(const vector<int> v)
{
  for (auto x = v.begin(); x != v.end(); ++x)
    cout << *x << (x != --v.end() ? ',' : ' ');
  cout << endl;
}

void swap(vector<int> &v, int i, int j)
{
  int t = v[i];
  v[i] = v[j];
  v[j] = t;
}

int main()
{
  vector<int> vec{10, 20, 30};
  swap(vec, 0, 2);
  print_vector_int(vec);

  return 0;
}