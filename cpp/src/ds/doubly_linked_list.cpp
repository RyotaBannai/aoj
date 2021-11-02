#include <iostream>
#include <string>
#define lp(i, n) for (int i = 0; i < n; i++)
using namespace std;

struct Node {
  int key;
  Node *next, *prev;
};

Node *nil;

auto listSearch(int key) -> Node *
{
  Node *cur = nil->next; // 番兵の次の要素から始める
  while (cur != nil && cur->key != key)
    cur = cur->next;
  return cur;
}

void init()
{
  nil = (Node *)malloc(sizeof(Node));
  nil->next = nil;
  nil->prev = nil;
}

void printList()
{
  Node *cur = nil->next;
  int isf = 0;
  while (true) {
    if (cur == nil)
      break;
    if (isf++ > 0)
      cout << " ";
    cout << cur->key;
    cur = cur->next;
  }
  cout << endl;
}

void deleteNode(Node *t)
{
  if (t == nil)
    return; // t が番兵の場合は処理しない
  t->prev->next = t->next;
  t->next->prev = t->prev;
  free(t);
}

void deleteFirst() { deleteNode(nil->next); }

void deleteLast() { deleteNode(nil->prev); }

void deleteKey(int key) { deleteNode(listSearch(key)); }

void insert(int key)
{
  Node *x = (Node *)malloc(sizeof(Node));
  x->key = key;
  // 番兵の直後に要素を追加
  x->next = nil->next;
  nil->next->prev = x;
  nil->next = x;
  x->prev = nil;
}

auto main() -> int
{
  int key, n, i;
  int size = 0;
  string com;
  int np = 0, nd = 0;
  cin >> n;
  init();
  lp(i, n)
  {
    cin >> com;
    if (com[0] == 'i') {
      cin >> key;
      insert(key), np++, size++;
    }
    else if (com[0] == 'd') {
      if (com.length() > 6) {
        if (com[6] == 'F')
          deleteFirst();
        else if (com[6] == 'L')
          deleteLast();
      }
      else {
        cin >> key;
        deleteKey(key), nd++;
      }
      size--;
    }
  }

  printList();
}