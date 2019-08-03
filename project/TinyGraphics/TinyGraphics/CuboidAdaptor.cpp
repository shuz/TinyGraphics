// CuboidAdaptor.cpp : implementation file
//

#include "stdafx.h"
#include "TinyGraphics.h"
#include "CuboidAdaptor.h"
#include "EditObjectDialog.h"
#include "Utilities.h"
#include "Kernel/Position.h"

using namespace TinyGraphics;

IMPLEMENT_SERIAL(CCuboidAdaptor, CObject, TG_VERSION + 1)

// CCuboidAdaptor

CCuboidAdaptor::CCuboidAdaptor()
{
  cuboid = 0;
  name = "Cuboid";
}

CCuboidAdaptor::CCuboidAdaptor(TinyGraphics::Cuboid *c, CString n)
{
  cuboid = c;
  name = n;
}

CCuboidAdaptor::~CCuboidAdaptor()
{
}


// CCuboidAdaptor member functions

void CCuboidAdaptor::Serialize(CArchive& ar) {
  CObject::Serialize(ar);

  if (ar.IsStoring()) {
    ar << name;
    real a, b, c;
    cuboid->get_extent(a, b, c);
    ar << a << b << c;
    ar << cuboid->get_position();
    ar << cuboid->get_material();
  } else {
    cuboid = new Cuboid();
    ar >> name;
    real a, b, c;
    ar >> a >> b >> c;
    cuboid->set_extent(a, b, c);
    Position pos;
    Material material;
    ar >> pos;
    ar >> material;
    cuboid->set_position(pos);
    cuboid->set_material(material);
  }
}

bool CCuboidAdaptor::EditObject() {
  real a, b, c;
  cuboid->get_extent(a, b, c);
  CEditObjectDialog dialog(cuboid->get_position(), cuboid->get_material(),
                           a, b, c, -1, -1, name);
  if (IDOK == dialog.DoModal()) {
    cuboid->set_position(Position(dialog.location, dialog.vf, dialog.vup));
    cuboid->set_extent(dialog.l, dialog.w, dialog.h);
    cuboid->set_material(dialog.GetMaterial());
    name = dialog.name;
    return true;
  }
  return false;
}
