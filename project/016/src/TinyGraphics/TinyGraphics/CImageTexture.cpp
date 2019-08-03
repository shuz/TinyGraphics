#include "StdAfx.h"

#include "CImageTexture.h"

#include "Kernel/Primitive2D.h"
#include "Kernel/ColorRGB.h"

using namespace TinyGraphics;

static inline
int round(real x) {
  return (int) (x + 0.5);
}

struct CImageTexture::Impl {
  CImage image;
  int scale_x, scale_y;
  CString filename;

  Impl() {}

  Impl(CString filename) : filename(filename) {
    HRESULT hResult = image.Load(filename);
    if (FAILED(hResult)) {
      throw LoadFailure(std::string(CString("Error loading texture: ") + filename));
    }
    scale_x = image.GetWidth() - 1;
    scale_y = image.GetHeight() - 1;
  }
};

CImageTexture::CImageTexture()
  : pimpl(new Impl()) {}

CImageTexture::CImageTexture(CString filename)
  : pimpl(new Impl(filename)) {}

CImageTexture::~CImageTexture() {
  delete pimpl;
}

ColorRGB CImageTexture::get_color(const Point2D& point) const {
  const real SCALE_FACTOR = 255.0;
  
  if (-TG_EPSILON <= point.x && point.x <= 1 + TG_EPSILON &&
      -TG_EPSILON <= point.y && point.y <= 1 + TG_EPSILON) {

    COLORREF color = pimpl->image.GetPixel(round(point.x * pimpl->scale_x),
                                           round((1 - point.y) * pimpl->scale_y));
    return ColorRGB(GetRValue(color)/SCALE_FACTOR,
                    GetGValue(color)/SCALE_FACTOR,
                    GetBValue(color)/SCALE_FACTOR);
  }
  return ColorRGB::BLACK;
}

const CImage *CImageTexture::get_image() const {
  return &pimpl->image;
}

CString CImageTexture::get_filename() const {
  return pimpl->filename;
}

void CImageTexture::set_image(const CImage *image) {
  pimpl->image = *image;
}
