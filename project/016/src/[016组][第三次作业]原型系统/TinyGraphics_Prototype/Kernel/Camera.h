#ifndef CAMERA_INCLUDED__
#define CAMERA_INCLUDED__

class Matrix4D;

class Camera {
public:
  virtual
  ~Camera() = 0;

  virtual
  const Matrix4D& get_normalization_matrix() const = 0;

  virtual
  const Matrix4D& get_projection_matrix() const = 0;

protected:
  Camera();

private:
  Camera(const Camera&);              // not implemented
  Camera& operator=(const Camera&);   // not implemented
};

#endif
