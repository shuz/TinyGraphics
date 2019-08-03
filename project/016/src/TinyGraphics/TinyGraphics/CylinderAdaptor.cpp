// CylinderAdaptor.cpp : implementation file
//

#include "stdafx.h"
#include "TinyGraphics.h"
#include "CylinderAdaptor.h"
#include "EditObjectDialog.h"
#include "Utilities.h"
#include "Kernel/Position.h"

using namespace TinyGraphics;

IMPLEMENT_SERIAL(CCylinderAdaptor, CObject, TG_VERSION + 1)

// CCylinderAdaptor

CCylinderAdaptor::CCylinderAdaptor()
{
  cylinder = 0;
  name = "Cylinder";
}

CCylinderAdaptor::CCylinderAdaptor(TinyGraphics::Cylinder *c, CString n)
{
  cylinder = c;
  name = n;
}

CCylinderAdaptor::~CCylinderAdaptor()
{
}


// CCylinderAdaptor member functions

void CCylinderAdaptor::Serialize(CArchive& ar) {
  CObject::Serialize(ar);

  if (ar.IsStoring()) {
    ar << name;
    real r, h;
    cylinder->get_radius_height(r, h);
    ar << r << h;
    ar << cylinder->get_position();
    ar << cylinder->get_material();
    ar << cylinder->get_resolution();
  } else {
    cylinder = new Cylinder();
    ar >> name;
    real r, h;
    ar >> r >> h;
    cylinder->set_radius_height(r, h);
    Position pos;
    Material material;
    int lx;
    ar >> pos;
    ar >> material;
    ar >> lx;
    cylinder->set_position(pos);
    cylinder->set_material(material);
    cylinder->set_resolution(lx);
  }
}

bool CCylinderAdaptor::EditObject() {
  real r, h;
  cylinder->get_radius_height(r, h);
  CEditObjectDialog dialog(cylinder->get_position(), cylinder->get_material(),
                           -1, -1, h, r, cylinder->get_resolution(), name);
  if (IDOK == dialog.DoModal()) {
    cylinder->set_position(Position(dialog.location, dialog.vf, dialog.vup));
    cylinder->set_radius_height(dialog.r, dialog.h);
    cylinder->set_material(dialog.GetMaterial());
    cylinder->set_resolution(dialog.lx);
    name = dialog.name;
    return true;
  }
  return false;
}
