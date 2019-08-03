// PointLightAdaptor.cpp : implementation file
//

#include "stdafx.h"
#include "TinyGraphics.h"
#include "PointLightAdaptor.h"
#include "EditLightDialog.h"
#include "Utilities.h"
#include "Kernel/PointLight.h"
#include "Kernel/Position.h"

using namespace TinyGraphics;

IMPLEMENT_SERIAL(CPointLightAdaptor, CObject, TG_VERSION + 1)

// CPointLightAdaptor

CPointLightAdaptor::CPointLightAdaptor()
{
  light = 0;
  name = "PointLight";
}

CPointLightAdaptor::CPointLightAdaptor(TinyGraphics::PointLight *l, CString n)
{
  light = l;
  name = n;
}

CPointLightAdaptor::~CPointLightAdaptor()
{
}


// CPointLightAdaptor member functions

void CPointLightAdaptor::Serialize(CArchive& ar) {
  CObject::Serialize(ar);

  if (ar.IsStoring()) {
    ar << name;
    ar << light->location;
    ar << light->attenuation;
    ar << light->color;
    ar << light->intensity;
  } else {
    light = new PointLight();
    ar >> name;
    ar >> light->location;
    ar >> light->attenuation;
    ar >> light->color;
    ar >> light->intensity;
  }
}

bool CPointLightAdaptor::EditObject() {
  CEditLightDialog dialog(light->location, Vector3D::ORIGIN, light->attenuation,
                           light->intensity, light->color, true, name);
  if (IDOK == dialog.DoModal()) {
    light->location = dialog.location;
    light->attenuation = dialog.attenuation;
    light->intensity = dialog.intensity;
    light->color = dialog.color;
    name = dialog.name;
    return true;
  }
  return false;
}
