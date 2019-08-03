// PlaneAdaptor.cpp : implementation file
//

#include "stdafx.h"
#include "TinyGraphics.h"
#include "PlaneAdaptor.h"
#include "EditObjectDialog.h"
#include "Utilities.h"
#include "Kernel/Position.h"

using namespace TinyGraphics;

IMPLEMENT_SERIAL(CPlaneAdaptor, CObject, TG_VERSION + 1)

// CPlaneAdaptor

CPlaneAdaptor::CPlaneAdaptor()
{
  plane = 0;
  name = "Plane";
}

CPlaneAdaptor::CPlaneAdaptor(TinyGraphics::Plane *c, CString n)
{
  plane = c;
  name = n;
}

CPlaneAdaptor::~CPlaneAdaptor()
{
}


// CPlaneAdaptor member functions

void CPlaneAdaptor::Serialize(CArchive& ar) {
  CObject::Serialize(ar);

  if (ar.IsStoring()) {
    ar << name;
    real a, b;
    plane->get_extent(a, b);
    ar << a << b;
    ar << plane->get_position();
    ar << plane->get_material();
  } else {
    plane = new Plane();
    ar >> name;
    real a, b;
    ar >> a >> b;
    plane->set_extent(a, b);
    Position pos;
    Material material;
    ar >> pos;
    ar >> material;
    plane->set_position(pos);
    plane->set_material(material);
  }
}

bool CPlaneAdaptor::EditObject() {
  real a, b;
  plane->get_extent(a, b);
  CEditObjectDialog dialog(plane->get_position(), plane->get_material(),
                           a, b, -1, -1, -1, name);
  if (IDOK == dialog.DoModal()) {
    plane->set_position(Position(dialog.location, dialog.vf, dialog.vup));
    plane->set_extent(dialog.l, dialog.w);
    plane->set_material(dialog.GetMaterial());
    name = dialog.name;
    return true;
  }
  return false;
}
