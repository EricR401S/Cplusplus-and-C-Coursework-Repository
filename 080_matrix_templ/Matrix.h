#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!

template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0){};
  Matrix(int r, int c) : numRows(r), numColumns(c) {
    rows = std::vector<std::vector<T> >(numRows, std::vector<T>(numColumns));
  };
  Matrix(const Matrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) {
    // makes a deep copy: copy constructor

    //rows.resize(rhs.numRows);

    rows = std::vector<std::vector<T> >(numRows, std::vector<T>(numColumns));

    for (int i = 0; i < rhs.getRows(); i++) {
      //
      //rows[i] = std::vector<T>();
      rows[i] = rhs.rows[i];
    }
  };
  ~Matrix(){};
  // Matrix & operator=(const Matrix & rhs) {
  //   //
  //   if (this == &rhs) {
  //     return *this;
  //   }

  //   if (rows != NULL) {  //|| this != &rhs) {
  //     rows.clear();
  //   }
  //   else {
  //     rows = std::vector<std::vector<T> >(numRows, std::vector<T>(numColumns));
  //   }
  //   // if rows are null
  //   numRows = rhs.numRows;
  //   numColumns = rhs.numColumns;
  //   //rows.resize(numRows);
  //   for (int i = 0; i < rhs.getRows(); i++) {
  //     //rows[i] = std::vector<T>();
  //     rows[i] = rhs.rows[i];
  //   }
  //   return *this;
  // }
  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }

  std::vector<T> & operator[](int index) {
    assert(index < numRows && index >= 0);
    return rows[index];
  }

  const std::vector<T> & operator[](int index) const {
    assert(index < numRows && index >= 0);
    return rows[index];  //*rows[index]
  }

  bool operator==(const Matrix & rhs) const {
    if (this == &rhs) {
      return true;
    }

    if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
      return false;
    }

    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        if ((*this)[i][j] != rhs[i][j]) {
          return false;
        }
        // if ((*this)[i] != rhs.rows[i]) {
        //   return false;
        // }
      }
    }
    return true;
  }

  Matrix operator+(const Matrix & rhs) const {
    //
    // - IntMatrix operator+(const IntMatrix & rhs) const;
    // o assert()s that this and rhs have the same dimensions.
    // o Returns matrix (also the same dimensions as this and rhs) whose
    //   elements are the sum of the corresponding elements of this
    //   matrix and rhs (does matrix addition).

    assert(numRows == rhs.numRows && numColumns == rhs.numColumns);

    Matrix ans(numRows, numColumns);

    //ans.rows.resize(numRows);

    for (int i = 0; i < numRows; i++) {
      //

      for (int j = 0; j < numColumns; j++) {
        ans[i][j] = (*this)[i][j] + rhs[i][j];
        //ans[i] = (*this)[i] + rhs[i];
        //(*(ans.rows[i]))[j] = (*(rows[i]))[j] + (*(rhs.rows[i]))[j];
      }
    }
    //std::cout << ans << std::endl;
    return ans;
  }

  //   friend std::ostream & operator<<(std::ostream & s, const Matrix & rhs) {
  //     //
  //     if (rhs.getRows() != 0) {
  //       s << "[ ";

  //       for (int i = 0; i < rhs.getRows(); i++) {
  //         if (i == (rhs.getRows() - 1)) {
  //           s << rhs[i] << " ]";
  //         }
  //         else {
  //           s << rhs[i] << ",\n";
  //         }
  //       }
  //     }

  //     else {
  //       s << "[  ]";
  //     }

  //     return s;
  //   }
};

template<typename T>
std::ostream & operator<<(std::ostream & os, const Matrix<T> & rhs) {
  os << "[ ";

  std::string rowdelim;
  for (int i = 0; i < rhs.getRows(); i++) {
    os << rowdelim << "{";
    rowdelim = ",\n";
    std::string coldedelim;
    for (int j = 0; j < rhs.getColumns(); j++) {
      os << coldedelim << rhs[i][j];
      coldedelim = ", ";
    }

    // if (i == rhs.getRows() - 1){
    //   os << "}";
    // }
    // else{
    os << "}";
  }
  os << " ]";

  return os;
}

// template<typename T>
// std::ostream & operator<<(std::ostream & s, const T & rhs) {
//   // print
//   if (rhs.getRows() != 0) {
//     s << "[ ";

//     for (int i = 0; i < rhs.size(); i++) {
//       if (i == (rhs.getRows() - 1)) {
//         s << rhs[i] << " ]";
//       }
//       else {
//         s << rhs[i] << ",\n";
//       }
//     }
//   }

//   else {
//     s << "[  ]";
//   }

//   return s;
//};
#endif
