#include <iostream>
#include <iomanip>
#include <cassert>
#include "Matrix4D.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// operation definitions

// prefix operators

// dot product
double dot(Vector4D& v1, Vector4D& v2) {
  double ret_val = 0;
  for (int j = 0; j < 4; ++j) {
    ret_val += v1[j] * v2[j];
  }
  return ret_val;
}

void multiply(Vector4D& ret_val, Vector4D& v, Matrix4D& m) {
  assert(&ret_val != &v);
  for (int i = 0; i < 4; ++i) {
    ret_val[i] = 0;
    for (int j = 0; j < 4; ++j) {
      ret_val[i] += v[j] * m[j][i];
    }
  }
}

void multiply(Matrix4D& ret_val, Matrix4D& m1, Matrix4D& m2) {
  assert(&ret_val != &m1 && &ret_val != &m2);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      ret_val[i][j] = 0;
      for (int k = 0; k < 4; ++k) {
        ret_val[i][j] +=  m1[i][k] * m2[k][j];
      }
    }
  }
}

void transpose(Matrix4D& ret_val, Matrix4D& m) {
  assert(&ret_val != &m);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      ret_val[i][j] = m[j][i];
    }
  }
}

//////////////////////////////////////////////////////////////////////
// utilities
std::ostream& operator<<(std::ostream& o, Matrix4D& m) {
  for (int i = 0; i < 4; ++i) {
    o << " | ";
    for (int j = 0; j < 4; ++j) {
      o << std::setw(3) << m[i][j] << " ";
    }
    o << " |\n";
  }
  return o;
}

std::ostream& operator<<(std::ostream& o, Vector4D& v) {
  o << "(";
  for (int i = 0; i < 3; ++i) {
    o << v[i] << ", ";
  }
  o << v[3] << ")";
  return o;
}
