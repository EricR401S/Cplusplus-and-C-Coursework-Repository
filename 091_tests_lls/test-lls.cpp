#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }

  void testCpCtor(const IntList & other) {
    IntList il(other);
    //assert(il.head == other.head);
    //assert(il.tail == other.tail);
    assert(il.getSize() == other.getSize());
    // test the copying that they did
    for (int i = 0; i < other.getSize(); i++) {
      //
      assert(il[i] == other[i]);
    }
  };

  void testdestructor(){
      // test the destructing mechanisms
      //IntList * il = new IntList;
      //delete il;
      //IntList * il2 = new IntList;
      // I don't think I have to destroy
  };

  void testassignmentCtor() {
    //testintg the assignment constructor
    // do it in body of code
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    il.addFront(7);
    assert(il[0] == 7);
    il.addFront(-35);
    assert(il[0] == -35);
    il.addFront(5);
    assert(il.head->data == 5);
    assert(il[1] == -35);
    assert(il.tail->data == 7);
    assert(il.getSize() == 3);
  };
  // many more tester methods
  void testAddBack() {
    // WRITE ME
    IntList il;
    il.addBack(7);
    assert(il[0] == 7);
    il.addBack(-35);
    assert(il[1] == -35);
    il.addBack(5);
    assert(il.tail->data == 5);
    assert(il[1] == -35);
    assert(il.head->data == 7);
    assert(il.getSize() == 3);
  };

  void testmixfrontback() {
    //mix both
    int arr[4] = {5, -35, 7, 10};
    IntList il;
    il.addBack(7);

    assert(il.head != NULL);
    assert(il.tail != NULL);
    assert(il.head->data == 7);
    assert(il.tail->data == 7);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);

    il.addFront(-35);
    il.addBack(10);
    il.addFront(5);
    il.addBack(29);
    assert(il.getSize() == 5);
    il.remove(29);

    // assert(il.head->data == 5);
    // assert(il[1] == -35);
    // assert(il[2] == 7);
    // assert(il.tail->data == 10);
    assert(il.getSize() == 4);

    // loop check prev and next

    assert(il.head != NULL);
    assert(il.head->next != NULL);
    assert(il.head->data == 5);
    assert(il.head->next->data == -35);
    assert(il.head->prev == NULL);

    assert(il.tail != NULL);
    assert(il.tail->data == 10);
    assert(il.tail->next == NULL);
    assert(il.tail->prev != NULL);
    assert(il.tail->prev->data == 7);

    IntList::Node * curr = il.head;  //node [1]
    for (int i = 0; i < il.getSize(); i++) {
      // check the connections
      // check all the connections
      assert(il[i] == arr[i]);

      if (i == 0) {
        assert(curr->prev == NULL);
        assert(curr->next != NULL);
        assert(curr->next->data == arr[i + 1]);
        assert(il.head != NULL);
        assert(il.head->next != NULL);
        assert(il.head->data == arr[i]);
        assert(il.head->next->data == arr[i + 1]);
        assert(il.head->prev == NULL);
      }

      else if (i != 0 && i != (il.getSize() - 1)) {
        assert(curr->prev != NULL);
        assert(curr->prev->data == arr[i - 1]);
        assert(curr->next != NULL);
        assert(curr->next->data == arr[i + 1]);
      }
      else if (i == il.getSize() - 1) {
        assert(curr->prev != NULL);
        assert(curr->prev->data == arr[i - 1]);
        assert(curr->next == NULL);
        assert(il.tail != NULL);
        assert(il.tail->data == arr[i]);
        assert(il.tail->next == NULL);
        assert(il.tail->prev != NULL);
        assert(il.tail->prev->data == arr[i - 1]);
      }
      curr = curr->next;
    }
  };

  void testremove() {
    // WRITE ME
    IntList il;
    il.addBack(7);
    il.addBack(-35);
    il.addBack(5);
    il.remove(5);
    assert(il.getSize() == 2);
    il.remove(7);
    assert(il.getSize() == 1);
    il.remove(-35);
    assert(il.getSize() == 0);
  };

  void test_complex_remove() {
    // check that the head changes after removal
    // check that the tail updates after removal
    // check that the next and prev updates after removal
    // check remove on empty list
    // check remove and additions and the pointers themselves
    IntList il;
    il.addBack(7);
    il.addBack(-35);
    il.addBack(5);
    il.addBack(5);
    il.addFront(10);
    assert(il.getSize() == 5);

    //check head and tail
    assert(il.head->data == 10);
    assert(il.head->next->data == 7);
    assert(il.head->prev == NULL);

    assert(il.tail->data == 5);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == 5);

    //check tail
    il.remove(5);
    assert(il.getSize() == 4);
    assert(il.tail->data == 5);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == -35);

    //check head
    il.remove(10);
    assert(il.getSize() == 3);
    assert(il.head->data == 7);
    assert(il.head->prev == NULL);
    assert(il.head->next->data == -35);

    // down the middle
    il.remove(-35);
    assert(il.getSize() == 2);
    assert(il.head->data == 7);
    assert(il.head->prev == NULL);
    assert(il.head->next->data == 5);

    assert(il.tail->data == 5);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == 7);

    // check single element list
    il.remove(5);
    assert(il.getSize() == 1);
    assert(il.head->data == 7);
    assert(il.head->prev == NULL);
    assert(il.head->next == NULL);

    assert(il.tail->data == 7);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == NULL);

    il.remove(7);
    assert(il.getSize() == 0);

    assert(il.head == NULL);
    assert(il.tail == NULL);

    il.addFront(3);
    assert(il.head->data == 3);
    assert(il.head->next == NULL);

    assert(il.head->prev == NULL);

    assert(il.tail->data == 3);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == NULL);

    il.addFront(21);
    assert(il.head->data == 21);
    assert(il.head->next->data == 3);
    assert(il.head->prev == NULL);

    assert(il.tail->data == 3);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == 21);

    // check the return value
    assert(il.remove(21) == true);
    assert(il.remove(100) == false);
    // assert(il.tail->next == NULL);
    // assert(il.tail->prev == NULL);

    // il.remove(7);
    // assert(il.getSize() == 1);
    // il.remove(-35);
    // assert(il.getSize() == 0);
  };
};
int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testremove();
  t.testmixfrontback();
  IntList my_il;
  my_il.addFront(1);
  my_il.addBack(2);
  my_il.addBack(-5);
  t.testCpCtor(my_il);

  IntList second_il;
  second_il.addFront(5);
  second_il.addBack(10);
  my_il = second_il;

  my_il.remove(-5);
  my_il.remove(2);
  my_il.remove(1);
  my_il.remove(1);

  t.test_complex_remove();
  // write calls to your other test methods here
  // test assignment constructor
  return EXIT_SUCCESS;
}
