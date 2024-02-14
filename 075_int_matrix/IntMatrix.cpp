#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0) {
  rows = NULL;  //new IntArray *[0]();
  // do not do anything
}

IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c) {
  rows = new IntArray *[r]();

  for (int i = 0; i < numRows; i++) {
    //
    rows[i] = new IntArray(numColumns);
  }
}

IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows), numColumns(rhs.numColumns) {
  // makes a deep copy: copy constructor
  rows = new IntArray *[numRows]();

  for (int i = 0; i < numRows; i++) {
    //
    rows[i] = new IntArray(numColumns);

    // assuming rhs has no NULL matrix, not sure

    for (int j = 0; j < rhs.rows[i]->size(); j++) {
      // copy the contents

      (*this)[i][j] = rhs[i][j];
      //rows[i][j] = rhs[i][j];
    }
  }
}
IntMatrix::~IntMatrix() {
  // Remember a case with forcefully initialized 0 rows and 0 columns
  for (int i = 0; i < numRows; i++) {
    //
    delete rows[i];
  }
  //check if checking for null is necessary
  delete[] rows;
}

IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  // deep copy via assignment

  if (this == &rhs) {
    return *this;
  }

  if (rows != NULL) {  //|| this != &rhs) {
    for (int i = 0; i < numRows; i++) {
      delete rows[i];  // changed from delete[]
    }
    delete[] rows;
  }

  else {
    // if rows are null
  }
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = new IntArray *[numRows]();

  for (int i = 0; i < numRows; i++) {
    //
    rows[i] = new IntArray(numColumns);

    // assuming rhs has no NULL matrix, not sure

    for (int j = 0; j < rhs.numColumns; j++) {  //used to be getsize or size
      // copy the contents

      (*this)[i][j] = rhs[i][j];
    }
  }

  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index < numRows && index >= 0);
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index) {
  assert(index < numRows && index >= 0);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (this == &rhs) {
    return true;
  }

  if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
    return false;
  }

  // for (int i = 0; i < numRows; i++) {
  //   //
  //   if (*rows[i] != *rhs.rows[i]) {
  //     return false;
  //   }
  // }

  for (int i = 0; i < numRows; i++) {
    //
    for (int j = 0; j < numColumns; j++) {
      if ((*this)[i][j] != rhs[i][j]) {
        return false;
      }
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  //
  // - IntMatrix operator+(const IntMatrix & rhs) const;
  // o assert()s that this and rhs have the same dimensions.
  // o Returns matrix (also the same dimensions as this and rhs) whose
  //   elements are the sum of the corresponding elements of this
  //   matrix and rhs (does matrix addition).
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);

  IntMatrix ans(numRows, numColumns);

  for (int i = 0; i < numRows; i++) {
    //

    for (int j = 0; j < numColumns; j++) {
      //
      ans[i][j] = (*this)[i][j] + rhs[i][j];
      //(*(ans.rows[i]))[j] = (*(rows[i]))[j] + (*(rhs.rows[i]))[j];
    }
  }
  //std::cout << ans << std::endl;
  return ans;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  // print

  //   Additionally, you will write an overloading of the << operator for
  // std::ostream & and const IntMatrix &:
  //   std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs);
  // This should print (to s) a "[ ", followed by each row of the matrix
  // (using IntArray's << operator). These rows should be separated by
  // ",\n". After the last row, you should print " ]" and return s.

  //if (rhs.getColumns() != 0 || rhs.getRows() != 0){
  if (rhs.getRows() != 0) {
    s << "[ ";

    for (int i = 0; i < rhs.getRows(); i++) {
      if (i == (rhs.getRows() - 1)) {
        s << rhs[i] << " ]";
      }
      else {
        s << rhs[i] << ",\n";
      }
    }
  }

  else {
    s << "[  ]";
  }

  return s;
}
