#include "StdAfx.h"
#include "Utilities.h"
#include "CImageTexture.h"
#include <stdexcept>

using namespace TinyGraphics;

const int COLOR_FACTOR = 0xFF;

COLORREF convert_color(const ColorRGB& color) {
  return RGB(color.red   * COLOR_FACTOR,
             color.green * COLOR_FACTOR,
             color.blue  * COLOR_FACTOR);
}

ColorRGB convert_color(COLORREF color) {
  return ColorRGB(
    GetRValue(color) / (real)COLOR_FACTOR,
    GetGValue(color) / (real)COLOR_FACTOR,
    GetBValue(color) / (real)COLOR_FACTOR
  );
}


CArchive& operator << (CArchive& ar, const Point3D& pos) {
  return ar << pos.x << pos.y << pos.z;
}

CArchive& operator >> (CArchive& ar, Point3D& pos) {
  return ar >> pos.x >> pos.y >> pos.z;
}


CArchive& operator << (CArchive& ar, const Vector3D& pos) {
  return ar << pos(0) << pos(1) << pos(2);
}

CArchive& operator >> (CArchive& ar, Vector3D& pos) {
  return ar >> pos(0) >> pos(1) >> pos(2);
}

CArchive& operator << (CArchive& ar, const ColorRGB& pos) {
  return ar << pos.red << pos.green << pos.blue;
}

CArchive& operator >> (CArchive& ar, ColorRGB& pos) {
  return ar >> pos.red >> pos.green >> pos.blue;
}

CArchive& operator << (CArchive& ar, const Position& pos) {
  return ar << pos.get_location() << pos.get_front_vector() << pos.get_up_vector();
}

CArchive& operator >> (CArchive& ar, Position& pos) {
  Point3D location;  Vector3D vf, vup;
  ar >> location >> vf >> vup;
  Position npos(location, vf, vup);
  pos = npos;
  return ar;
}

CArchive& operator << (CArchive& ar, const Material& mat) {
  ar << mat.color << mat.k_ambient << mat.k_specular << mat.shininess
     << mat.k_diffuse << mat.k_transparency << mat.refraction_index;
  if (mat.texture == 0) {
    ar << false;
  } else {
    ar << true;
    CImageTexture *texture = (CImageTexture *)mat.texture;
    ar << texture->get_filename();
  }
  return ar;
}

CArchive& operator >> (CArchive& ar, Material& mat) {
  ar >> mat.color >> mat.k_ambient >> mat.k_specular >> mat.shininess
     >> mat.k_diffuse >> mat.k_transparency >> mat.refraction_index;
  mat.texture = 0;
  bool is_textured;
  ar >> is_textured;
  if (is_textured) {
    CString filename;
    ar >> filename;
    try {
      CImageTexture *texture = new CImageTexture(filename);
      mat.texture = texture;
    } catch (const CImageTexture::LoadFailure& except) {
      AfxMessageBox(CString("Error: ") + except.what(), NULL, MB_OK | MB_ICONERROR);
    }
  }
  return ar;
}
