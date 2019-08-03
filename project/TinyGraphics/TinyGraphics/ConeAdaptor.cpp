// ConeAdaptor.cpp : implementation file
//

#include "stdafx.h"
#include "TinyGraphics.h"
#include "ConeAdaptor.h"
#include "EditObjectDialog.h"
#include "Utilities.h"
#include "Kernel/Position.h"

using namespace TinyGraphics;

IMPLEMENT_SERIAL(CConeAdaptor, CObject, TG_VERSION + 1)

// CConeAdaptor

CConeAdaptor::CConeAdaptor()
{
  cone = 0;
  name = "Cone";
}

CConeAdaptor::CConeAdaptor(TinyGraphics::Cone *c, CString n)
{
  cone = c;
  name = n;
}

CConeAdaptor::~CConeAdaptor()
{
}


// CConeAdaptor member functions

void CConeAdaptor::Serialize(CArchive& ar) {
  CObject::Serialize(ar);

  if (ar.IsStoring()) {
    ar << name;
    real r, h;
    cone->get_radius_height(r, h);
    ar << r << h;
    ar << cone->get_position();
    ar << cone->get_material();
    ar << cone->get_resolution();
  } else {
    cone = new Cone();
    ar >> name;
    real r, h;
    ar >> r >> h;
    cone->set_radius_height(r, h);
    Position pos;
    Material material;
    int lx;
    ar >> pos;
    ar >> material;
    ar >> lx;
    cone->set_position(pos);
    cone->set_material(material);
    cone->set_resolution(lx);
  }
}

bool CConeAdaptor::EditObject() {
  real r, h;
  cone->get_radius_height(r, h);
  CEditObjectDialog dialog(cone->get_position(), cone->get_material(),
                           -1, -1, h, r, cone->get_resolution(), name);
  if (IDOK == dialog.DoModal()) {
    cone->set_position(Position(dialog.location, dialog.vf, dialog.vup));
    cone->set_radius_height(dialog.r, dialog.h);
    cone->set_material(dialog.GetMaterial());
    cone->set_resolution(dialog.lx);
    name = dialog.name;
    return true;
  }
  return false;
}
