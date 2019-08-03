#ifndef CIMAGE_TEXTURE_INCLUDED__
#define CIMAGE_TEXTURE_INCLUDED__

#include "Kernel/Texture.h"
#include <stdexcept>
#include <atlimage.h>

using namespace TinyGraphics;

class CImageTexture : public Texture {
public:
  struct LoadFailure : public std::runtime_error {
    LoadFailure(const std::string& msg) : std::runtime_error(msg) {}
  };

  CImageTexture();
  CImageTexture(CString filename);
  ~CImageTexture();

  ColorRGB get_color(const Point2D& point) const;

  CString get_filename() const;

  const CImage *get_image() const;
  void set_image(const CImage *image);

private:
  struct Impl;
  Impl *pimpl;
};

#endif
