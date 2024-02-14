#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>

//YOUR CODE GOES HERE

class index_not_found : public std::exception {
  const char * what() const throw() { return "Data not found at the index"; }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;

    //constructors
    Node(const T & d) : data(d), next(NULL), prev(NULL){};
    Node(const T & d, Node * n) : data(d), next(n), prev(NULL){};
    Node(const T & d, Node * n, Node * p) : data(d), next(n), prev(p) {}
    Node(const Node & n) : data(n.data), next(n.next), prev(n.prev) {}
  };
  Node * head;
  Node * tail;

 public:
  //methods

  //add constructors

  // add methods

  LinkedList() : head(NULL), tail(NULL){};

  LinkedList(const LinkedList & rhs) {
    Node * rhscurr = rhs.head;
    Node * cp_curr = NULL;
    Node * temp = NULL;
    while (rhscurr != NULL) {
      if (rhscurr == rhs.head) {
        cp_curr = new Node(rhscurr->data);
        head = cp_curr;
        tail = cp_curr;
        temp = cp_curr;
      }

      else if (rhscurr == rhs.tail) {
        cp_curr = new Node(rhscurr->data);
        tail = cp_curr;
        temp->next = cp_curr;
        cp_curr->prev = temp;
        temp = cp_curr;
      }

      else {
        cp_curr = new Node(rhscurr->data);
        temp->next = cp_curr;
        cp_curr->prev = temp;
        temp = cp_curr;
      }

      rhscurr = rhscurr->next;
    }
  }

  ~LinkedList() {
    if (head == NULL && tail == NULL) {
      return;
    }

    else {
      Node * temp = head;
      Node * curr = head;
      while (curr != NULL) {
        curr = curr->next;
        delete temp;
        temp = curr;
      }
    }
  }

  LinkedList & operator=(LinkedList & rhs) {
    // copy constructor magic
    //LinkedList * temporary = new LinkedList(rhs);
    LinkedList rhs_copy = LinkedList(rhs);

    if (head == NULL && tail == NULL) {
      // do nothing, because it means no memory has to be cleaned
    }

    else {
      // delete pre-existing memory
      Node * temp = head;
      Node * curr = head;
      while (curr != NULL) {
        curr = curr->next;
        delete temp;
        temp = curr;
      }
    }

    // try swapping

    Node * rhscurr_cp = rhs_copy.head;
    // Node * new_head = NULL;
    // Node * new_tail = NULL;
    Node * cp_curr = NULL;
    Node * temp2 = NULL;

    while (rhscurr_cp != NULL) {
      if (rhscurr_cp == rhs_copy.head) {
        cp_curr = new Node(rhscurr_cp->data);
        head = cp_curr;
        tail = cp_curr;
        temp2 = cp_curr;
      }

      else if (rhscurr_cp == rhs_copy.tail) {
        cp_curr = new Node(rhscurr_cp->data);
        tail = cp_curr;
        temp2->next = cp_curr;
        cp_curr->prev = temp2;
        temp2 = cp_curr;
      }

      else {
        cp_curr = new Node(rhscurr_cp->data);
        temp2->next = cp_curr;
        cp_curr->prev = temp2;
        temp2 = cp_curr;
      }

      rhscurr_cp = rhscurr_cp->next;
    }

    // head = temporary->head;
    // tail = temporary->tail;

    return *this;
  }

  int getSize() const {
    int counter = 0;
    Node * curr = head;
    while (curr != NULL) {
      counter++;
      curr = curr->next;
    }
    return counter;
  }

  void addFront(const T & item) {
    // Add to the front of the LL

    if (head == NULL && tail == NULL) {
      Node * new_node = new Node(item);
      head = new_node;
      tail = new_node;
    }

    else {
      //
      Node * temp = head;
      Node * new_node = new Node(item, head, NULL);
      temp->prev = new_node;
      head = new_node;
    }
  }

  void addBack(const T & item) {
    if (head == NULL && tail == NULL) {
      Node * new_node = new Node(item);
      head = new_node;
      tail = new_node;
    }

    else {
      //
      Node * temp = tail;
      Node * new_node = new Node(item, NULL, tail);
      temp->next = new_node;
      tail = new_node;
    }
  }
  bool remove(const T & item) {
    // - A "bool remove(const T & item)" method, which removes the
    // specified item from the list (assume that == is overloaded on
    // Ts, and use it to tell if you have the item you want). This
    // should return true if an item was actually removed and false if
    // no such item existed. You should only remove the first item
    // (starting from the head) if there are multiple items that match.

    if (head == tail) {  // same one, just one item
      if (head->data == item) {
        Node * temp = head;
        head = NULL;
        tail = NULL;
        //std::cout << "Any ideas?\n";
        delete temp;
        return true;
      }
    }

    else {
      // remove from ll
      Node * curr = head;
      while (curr != NULL) {
        if (curr->data == item && getSize() == 1) {
          delete curr;
          head = NULL;
          tail = NULL;
          return true;
        }

        else if (curr->data == item) {
          if (curr == head) {
            // when the data is the head
            //Node * temp = curr;
            head = head->next;
            head->prev = NULL;  // new head
            delete curr;
            return true;
          }

          else if (tail->data == item) {
            Node * temp = tail->prev;
            tail->prev->next = NULL;
            delete tail;
            tail = temp;
            return true;
          }
          else {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            delete curr;
            return true;
          }
        }
        curr = curr->next;
      }
    }
    return false;
  }

  T & operator[](int index) {
    //  - A "T & operator[](int index)" method, which gives a reference to
    // the data in the "index" element (starting from 0). You should
    // make an exception class (which extends std::exception) and throw
    // an instance of it when the requested item does not exist. You
    // should write a "const" and a "non-const" version of this.

    int counter = 0;
    bool found = false;
    Node * curr = head;
    while (curr != NULL) {
      if (counter == index) {
        found = true;
        break;
        //return curr->data;
      }
      else {
        counter++;
        curr = curr->next;
      }
    }

    if (!found) {
      std::cout << "trouble found\n";
      throw index_not_found();
    }

    return curr->data;
  }

  T & operator[](int index) const {
    //  - A "T & operator[](int index)" method, which gives a reference to
    // the data in the "index" element (starting from 0). You should
    // make an exception class (which extends std::exception) and throw
    // an instance of it when the requested item does not exist. You
    // should write a "const" and a "non-const" version of this.

    int counter = 0;
    bool found = false;
    Node * curr = head;
    while (curr != NULL) {
      if (counter == index) {
        found = true;
        break;
        //return curr->data;
      }
      else {
        counter++;
        curr = curr->next;
      }
    }

    if (!found) {
      std::cout << "trouble found\n";
      throw index_not_found();
    }

    return curr->data;
  }

  int find(const T & item) const {
    //index of the item in the list or -1 if no such item exists.}

    int counter = 0;
    Node * curr = head;
    while (curr != NULL) {
      if (curr->data == item) {
        return counter;
      }
      else {
        counter++;
        curr = curr->next;
      }
    }
    return -1;
  }

  friend class Tester;
};

typedef LinkedList<int> IntList;

#endif
