#ifndef TRANSFORM_INCLUDED__
#define TRANSFORM_INCLUDED__

//////////////////////////////////////////////////////////////////////
// standard transform matrices

class Matrix4D;
struct Point3D;

// assign Matrix4D m to be the matrix specified 
// by the name of the functions

void Identity(Matrix4D& m);

void Zero(Matrix4D& m);

void Transfer(double dx, double dy, double dz, Matrix4D& m);

void Scale(double sx, double sy, double sz, Matrix4D& m);

void RotateX(double theta, Matrix4D& m);

void RotateY(double theta, Matrix4D& m);

void RotateZ(double theta, Matrix4D& m);

void ShearXY(double shx, double shy, Matrix4D& m);

// create a parallel project matrix whose project direction is
// specified by a vector from the origin to point d, and the
// prject plane is specified by equation z = zp
// param d is not changed.
void ParallelProject(double zp, Point3D& d, Matrix4D& m);

#endif
