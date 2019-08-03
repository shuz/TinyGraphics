// SphereAdaptor.cpp : implementation file
//

#include "stdafx.h"
#include "TinyGraphics.h"
#include "SphereAdaptor.h"
#include "EditObjectDialog.h"
#include "Utilities.h"
#include "Kernel/Position.h"

using namespace TinyGraphics;

IMPLEMENT_SERIAL(CSphereAdaptor, CObject, TG_VERSION + 1)

// CSphereAdaptor

CSphereAdaptor::CSphereAdaptor()
{
  sphere = 0;
  name = "Sphere";
}

CSphereAdaptor::CSphereAdaptor(TinyGraphics::Sphere *c, CString n)
{
  sphere = c;
  name = n;
}

CSphereAdaptor::~CSphereAdaptor()
{
}


// CSphereAdaptor member functions

void CSphereAdaptor::Serialize(CArchive& ar) {
  CObject::Serialize(ar);

  if (ar.IsStoring()) {
    ar << name;
    ar << sphere->get_radius();
    ar << sphere->get_position();
    ar << sphere->get_material();
    ar << sphere->get_resolution();
  } else {
    sphere = new Sphere();
    ar >> name;
    real r;
    ar >> r ;
    sphere->set_radius(r);
    Position pos;
    Material material;
    int lx;
    ar >> pos;
    ar >> material;
    ar >> lx;
    sphere->set_position(pos);
    sphere->set_material(material);
    sphere->set_resolution(lx);
  }
}

bool CSphereAdaptor::EditObject() {
  CEditObjectDialog dialog(sphere->get_position(), sphere->get_material(),
                           -1, -1, -1, sphere->get_radius(), sphere->get_resolution(), name);
  if (IDOK == dialog.DoModal()) {
    sphere->set_position(Position(dialog.location, dialog.vf, dialog.vup));
    sphere->set_radius(dialog.r);
    sphere->set_material(dialog.GetMaterial());
    sphere->set_resolution(dialog.lx);
    name = dialog.name;
    return true;
  }
  return false;
}
