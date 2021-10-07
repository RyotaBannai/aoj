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
  T inp;
  cin >> inp;
  return inp;
}

auto allocNode() -> Node * { return (Node *)malloc(sizeof(Node)); }

void insert(int v)
{
  Node *y = NIL;
  Node *x = root;
  Node *z = allocNode(); // create new Node
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

auto treeMin(Node *u) -> Node *
{
  while (u->left != NIL)
    u = u->left;
  return u;
}

auto treeSuccessor(Node *u) -> Node *
{
  if (u->right != NIL)
    return treeMin(u->right);
  else {
    Node *y = u->parent;
    while (y != NIL && u == y->right) {
      u = y;         // right かどうかチェックのため
      y = y->parent; // 上へ登る
    }
    return y;
  }
}

void deleteNode(Node *u)
{
  Node *tar;      // 削除対象
  Node *sub_tree; // y の子

  if (u->left == NIL || u->right == NIL)
    // if both or either of children are/is NIL
    // 末端の Node ならそれを削除、子が１つの時は、それ自体を削除し、削除した場所に子を置く
    tar = u;
  else
    // 子が二つある場合は、中順巡回で次になる子を削除対象とする
    // 中順巡回で次のノードを探した時に、必ずそのノードは左側のノードを持つことはない（持っている場合、そのノードが次のノードになるため）
    tar = treeSuccessor(u);

  // 上記の else のロジックの通り、左側に sub tree があるケースが無いため必然的に right
  // が次の子となる
  sub_tree = tar->left != NIL ? tar->left : tar->right;
  if (sub_tree != NIL)
    sub_tree->parent = tar->parent;

  if (tar->parent == NIL)
    // 削除対象が root の場合
    root = sub_tree;
  else {
    if (tar == tar->parent->left)
      tar->parent->left = sub_tree;
    else
      tar->parent->right = sub_tree;
  }

  if (tar != u)
    u->key = tar->key;
  free(tar);
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
  int n, i;
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
    else if (com[0] == 'd')
      deleteNode(find(root, in<int>()));
  }

  return 0;
}