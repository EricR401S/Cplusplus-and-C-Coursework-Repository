#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {
}

IntArray::IntArray(int n) : numElements(n) {
  data = new int[n];
}

IntArray::IntArray(const IntArray & rhs) : numElements(rhs.numElements) {
  //- A copy constructor
  //o Performs a deep copy

  data = new int[numElements];

  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}

IntArray::~IntArray() {
  // destructor
  //- A destructor
  //o Releases any allocated memory

  if (data != NULL) {
    delete[] data;
  }
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  // Overloading the assignment operator

  if (this != &rhs) {
    numElements = rhs.numElements;
    if (data != NULL) {
      delete[] data;
    }
    data = new int[numElements];

    for (int i = 0; i < numElements; i++) {
      data[i] = rhs.data[i];
    }
  }
  return *this;
}

const int & IntArray::operator[](int index) const {
  // check if index is in bounds

  assert((index < numElements) && (index >= 0));

  return data[index];
}
int & IntArray::operator[](int index) {
  // check if index is in bounds

  assert((index < numElements) && (index >= 0));

  return data[index];
}

int IntArray::size() const {
  // return size of array

  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (this == &rhs) {
    return true;
  }

  // if ((rhs == NULL) && (*this != NULL)) {
  //   return false;
  // }

  if (rhs.numElements != numElements) {
    return false;
  }

  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return false;
    }
  }

  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  // if (this != &rhs) {
  //   return true;
  // }

  // if ((rhs == NULL) && (*this != NULL)) {
  //   return true;
  // }

  // if (rhs.numElements != numElements) {
  //   return true;
  // }

  // for (int i = 0; i < numElements; i++) {
  //   if (data[i] != rhs.data[i]) {
  //     return true;
  //   }
  // }

  // return false;

  if (*this == rhs) {
    return false;
  }

  else {
    return true;
  }
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  // printing

  if (rhs.size() != 0) {
    s << "{";

    for (int i = 0; i < rhs.size(); i++) {
      if (i == (rhs.size() - 1)) {
        s << rhs[i] << "}";
      }
      else {
        s << rhs[i] << ", ";
      }
    }
  }

  else {
    s << "{ }";  //{}
  }

  //s << "}";

  return s;
}
