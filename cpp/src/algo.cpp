#include <complex>
#include <iostream>
using namespace std;

/*
  $ g++ -o <name-you-want-to-give> source.cpp -> this compile with C++98
  to compile as C++11
  $ clang++ -std=c++11 -stdlib=libc++ -Weverything intro.cpp
  ref:
  https://stackoverflow.com/questions/14228856/how-to-compile-c-with-c11-support-in-mac-terminal
*/

static double square(double x) { return x * x; }

static void print_square(double x) { cout << "the square of " << x << " is " << square(x) << endl; }

static void check_cplusplus_version()
{
  if (__cplusplus == 201703L)
    std::cout << "C++17\n";
  else if (__cplusplus == 201402L)
    std::cout << "C++14\n";
  else if (__cplusplus == 201103L)
    std::cout << "C++11\n";
  else if (__cplusplus == 199711L)
    std::cout << "C++98\n";
  else
    std::cout << "pre-standard C++\n";
}

int main()
{
  // print_square(1.234);
  check_cplusplus_version();
}