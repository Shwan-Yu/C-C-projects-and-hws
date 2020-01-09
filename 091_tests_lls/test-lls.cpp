#include <assert.h>

#include <iostream>
#include <vector>

#include "il.h"

void testList() {
  IntList ll = IntList();

  assert(ll.size == 0);
  assert(ll.head == NULL);
  assert(ll.tail == NULL);
  ll.addFront(1);
  assert(ll.size == 1);
  assert(ll.head == ll.tail);
  assert(ll.head != NULL);
  ll.addFront(-1);
  assert(ll.size == 2);
  assert(ll.getSize() == 2);
  assert(ll[0] == -1);
  assert(ll[1] == 1);
  assert(ll.head->next->next == NULL);
  assert(ll.head->next == ll.tail);

  IntList ll2 = IntList(ll);
  IntList ll3;
  ll3 = ll;
  ll.~IntList();
  ll = ll3;
  assert(ll2.size == 2);
  assert(ll2[0] == -1);
  assert(ll2[1] == 1);
  assert(ll2.head->next->next == NULL);
  assert(ll2.head->next == ll2.tail);

  assert(ll3.size == 2);
  assert(ll3[0] == -1);
  assert(ll3[1] == 1);
  assert(ll3.head->next->next == NULL);
  assert(ll3.head->next == ll3.tail);
  assert(ll3.tail->prev == ll3.head);

  ll2.addFront(-1);
  ll3.addFront(10);
  assert(ll.size == 2);
  assert(ll[0] == -1);
  assert(ll[1] == 1);
  assert(ll.head->next->next == NULL);
  assert(ll.head->next == ll.tail);

  ll3.addFront(10);
  ll3.remove(ll3[1]);
  ll3.~IntList();

  ll.addBack(100);
  assert(ll.size == 3);
  assert(ll[0] == -1);
  assert(ll[1] == 1);
  assert(ll[2] == 100);
  assert(ll.head->next->next->next == NULL);
  assert(ll.head->next->next == ll.tail);
  assert(ll.tail->prev->prev == ll.head);
  ll.remove(7);
  assert(ll.size == 3);
  assert(ll[0] == -1);
  assert(ll[1] == 1 && ll[2] == 100);
  assert(ll.head->next->next->next == NULL);
  assert(ll.head->next->next == ll.tail);
  assert(ll.tail->prev->prev == ll.head);
  ll.remove(1);
  assert(ll.size == 2);
  assert(ll[0] == -1);
  assert(ll[1] == 100);
  assert(ll.head->next->next == NULL);
  assert(ll.head->next == ll.tail);
  assert(ll.tail->prev == ll.head);
  ll.remove(-1);
  assert(ll.size == 1);
  assert(ll[0] == 100);
  assert(ll.head->next == NULL);
  assert(ll.head == ll.tail);
  ll.remove(100);
}

int main() {
  testList();
  return EXIT_SUCCESS;
}
