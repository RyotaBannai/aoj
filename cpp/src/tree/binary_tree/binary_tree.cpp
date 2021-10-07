#include <cstdio>
#include <iostream>
#include <vector>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;

struct Node {
  int key;
  Node *parent, *left, *right;
};

Node *root, *NIL;

template <typename T> auto in() -> T
{
  int inp;
  cin >> inp;
  return inp;
}

void insert(int v)
{
  Node *y = NIL;
  Node *x = root;
  Node *z;

  // create new Node
  z = (Node *)malloc(sizeof(Node));
  z->key = v;
  z->left = NIL;
  z->right = NIL;

  while (x != NIL) {
    y = x;
    x = z->key < x->key ? x->left : x->right;
  }

  z->parent = y;
  if (y == NIL)
    root = z;
  else {
    if (z->key < y->key)
      y->left = z;
    else
      y->right = z;
  }
}

auto find(Node *u, int v) -> Node *
{
  while (u != NIL && u->key != v)
    u = v < u->key ? u->left : u->right;
  return u;
}

void inorder(Node *u)
{
  if (u == NIL)
    return;
  inorder(u->left);
  printf(" %d", u->key);
  inorder(u->right);
}

void preorder(Node *u)
{
  if (u == NIL)
    return;
  printf(" %d", u->key);
  preorder(u->left);
  preorder(u->right);
}

auto main() -> int
{
  int n, i, x;
  string com;

  cin >> n;
  lp(i, n)
  {
    cin >> com;
    if (com[0] == 'i')
      insert(in<int>());
    else if (com[0] == 'p') {
      inorder(root);
      printf("\n");
      preorder(root);
      printf("\n");
    }
    else if (com[0] == 'f')
      printf("%s\n", find(root, in<int>()) != NIL ? "yes" : "no");
  }

  return 0;
}
