#ifndef MATRIX_4D_INCLUDED__
#define MATRIX_4D_INCLUDED__

#include <iosfwd>

struct Vector4D {
private:
  double vec[4];

public:
  double& operator[](int i) {
    return vec[i];
  }
  Vector4D() {}
  Vector4D(double a, double b, double c, double d) {
    assign(a, b, c, d);
  }

  void assign(double a, double b, double c, double d) {
    vec[0] = a;   vec[1] = b;
    vec[2] = c;   vec[3] = d;
  }
};

// simple matrix 4D
class Matrix4D  
{
private:
  double mat[4*4];
public:

  // Proxy
  struct RowProxy {
  private:
    double *row;
  public:
    double& operator[](int i) {
      return row[i];
    }
    operator Vector4D() {
      return Vector4D(row[0], row[1], row[2], row[3]);
    }
    
    void operator=(Vector4D& v) {
      row[0] = v[0]; row[1] = v[1];
      row[2] = v[2]; row[3] = v[3];
    }
  private:
    RowProxy(double *r) : row(r) {}

    friend class Matrix4D;
  }; // Proxy

  RowProxy operator[](int i) {
    return RowProxy(mat + 4*i);
  }

  Matrix4D() {}
  Matrix4D(Vector4D v[]) {
    (*this)[0] = v[0];  (*this)[1] = v[1];
    (*this)[2] = v[2];  (*this)[3] = v[3];
  }
};

//////////////////////////////////////////////////////////////////////
// operations

// prefix operators
// note: ret_val in multiply can't be any of its operands
//       or you'll probably get the wrong answer!

double dot(Vector4D& v1, Vector4D& v2);     // dot product
void multiply(Vector4D& ret_val, Vector4D& v, Matrix4D& m);
void multiply(Matrix4D& ret_val, Matrix4D& m1, Matrix4D& m2);
void transpose(Matrix4D& ret_val, Matrix4D& m);

// infix operators

inline
double operator*(Vector4D& v1, Vector4D& v2) {      // dot product
  return dot(v1, v2);
}

inline
Vector4D operator*(Vector4D& v, Matrix4D& m) {
  Vector4D ret_val;
  multiply(ret_val, v, m);
  return ret_val;
}

inline
Matrix4D operator*(Matrix4D& m1, Matrix4D& m2) {
  Matrix4D ret_val;
  multiply(ret_val, m1, m2);
  return ret_val;
}

//////////////////////////////////////////////////////////////////////
// utilities
std::ostream& operator<<(std::ostream& o, Matrix4D& m);
std::ostream& operator<<(std::ostream& o, Vector4D& v);

inline
bool operator==(Vector4D& v1, Vector4D& v2) {
  return v1[0] == v2[0] &&
         v1[1] == v2[1] &&
         v1[2] == v2[2] &&
         v1[3] == v2[3];
}

inline
bool operator!=(Vector4D& v1, Vector4D& v2) {
  return !(v1 == v2);
}

#endif
