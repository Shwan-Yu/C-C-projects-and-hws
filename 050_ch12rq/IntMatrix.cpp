#include "IntMatrix.h"

#include <algorithm>
#include <iostream>

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}
IntMatrix::IntMatrix(int r, int c) :
    numRows(r),
    numColumns(c),
    rows(new IntArray *[numRows]) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray[numColumns];
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows),
    numColumns(rhs.numColumns),
    rows(new IntArray *[rhs.numRows]) {
  for (int i = 0; i < numRows; i++) {
    //can remove?
    rows[i] = new IntArray[numColumns];
    *(rows[i]) = *(rhs.rows[i]);
  }
}
IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    IntArray ** tmp = new IntArray *[numRows];
    for (int i = 0; i < numRows; i++) {
      tmp[i] = new IntArray[numColumns];
      *(tmp[i]) = *(rhs.rows[i]);
    }
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = tmp;
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
  assert(index >= 0 && index < numRows);
  return *(rows[index]);
}
IntArray & IntMatrix::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return *(rows[index]);
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (this == &rhs) {
    return true;
  }
  else if ((numRows != rhs.numRows) || (numColumns != rhs.numColumns)) {
    return false;
  }
  else {
    for (int i = 0; i < rhs.numRows; i++) {
      if (*(rows[i]) != *(rhs.rows[i])) {
        return false;
      }
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));
  for (int i = 0; i < rhs.numRows; i++) {
    for (int j = 0; j < rhs.numColumns; j++) {
      (*(rows[i]))[j] += (*(rhs.rows[i]))[j];
    }
  }
  return *this;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << rhs[i];
    if (i != rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << "]";
  return s;
}
