// WorldAdaptor.cpp : implementation file
//

#include "stdafx.h"
#include "TinyGraphics.h"

#include "Kernel/ColorRGB.h"

#include "EditWorldDialog.h"
#include "Utilities.h"

#include "WorldAdaptor.h"

using namespace TinyGraphics;

IMPLEMENT_SERIAL(CWorldAdaptor, CObject, TG_VERSION + 1)

// CWorldAdaptor

CWorldAdaptor::CWorldAdaptor()
{
  world = 0;
  m_nextObjNum = 1;
}

CWorldAdaptor::CWorldAdaptor(World3D *w)
{
  world = w;
  m_nextObjNum = 1;
}

CWorldAdaptor::~CWorldAdaptor()
{
}

// CWorldAdaptor member functions

void CWorldAdaptor::Serialize(CArchive& ar)
{
  CObject::Serialize(ar);

  if (ar.IsStoring())
  {	// storing code
    ar << world->get_ambient_color();
    ar << world->get_background_color();
    ar << world->get_refraction_index();
    ar << m_nextObjNum;
  }
  else
  {	// loading code
    ColorRGB color;
    ar >> color;
    world->set_ambient_color(color);
    ar >> color;
    world->set_background_color(color);
    real ridx;
    ar >> ridx;
    world->set_refraction_index(ridx);
    ar >> m_nextObjNum;
  }
}


bool CWorldAdaptor::EditObject() {
  CEditWorldDialog dialog(world->get_ambient_color(), world->get_background_color(),
                          world->get_refraction_index(), m_nextObjNum);
  if (IDOK == dialog.DoModal()) {
    world->set_ambient_color(dialog.ambientColor);
    world->set_background_color(dialog.backgroundColor);
    world->set_refraction_index(dialog.refract_idx);
    m_nextObjNum = dialog.next_obj_num;
    return true;
  }

  return false;
}
