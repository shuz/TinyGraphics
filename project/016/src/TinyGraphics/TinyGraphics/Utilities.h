#pragma once

#include "Kernel/ColorRGB.h"
#include "Kernel/Material.h"
#include "Kernel/Position.h"
#include "Kernel/Vector3D.h"
#include "Kernel/Primitive3D.h"

using namespace TinyGraphics;

ColorRGB convert_color(COLORREF c);
COLORREF convert_color(const ColorRGB& c);


CArchive& operator << (CArchive& ar, const Point3D& pos);
CArchive& operator >> (CArchive& ar, Point3D& pos);
CArchive& operator << (CArchive& ar, const Vector3D& pos);
CArchive& operator >> (CArchive& ar, Vector3D& pos);
CArchive& operator << (CArchive& ar, const ColorRGB& pos);
CArchive& operator >> (CArchive& ar, ColorRGB& pos);
CArchive& operator << (CArchive& ar, const Position& pos);
CArchive& operator >> (CArchive& ar, Position& pos);
CArchive& operator << (CArchive& ar, const Material& mat);
CArchive& operator >> (CArchive& ar, Material& mat);