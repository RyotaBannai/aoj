#include <iostream>
using namespace std;

static int getChar(char ch)
{
  if (ch == 'A')
    return 1;
  else if (ch == 'C')
    return 2;
  else if (ch == 'G')
    return 3;
  else if (ch == 'T')
    return 4;
  else
    0;
}

static long long getKey(char str[])
{
  long long sum = 0, p = 1, i;
  for (i = 0; i < strlen(str); i++) {
    sum += p * (getChar(str[i]));
    p *= 5;
  }
  return sum;
}

int main() { cout << getKey("AAA") << "\n"; }