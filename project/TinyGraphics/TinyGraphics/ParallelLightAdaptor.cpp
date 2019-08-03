// ParallelLightAdaptor.cpp : implementation file
//

#include "stdafx.h"
#include "TinyGraphics.h"
#include "ParallelLightAdaptor.h"
#include "EditLightDialog.h"
#include "Utilities.h"
#include "Kernel/ParallelLight.h"
#include "Kernel/Position.h"

using namespace TinyGraphics;

IMPLEMENT_SERIAL(CParallelLightAdaptor, CObject, TG_VERSION + 1)

// CParallelLightAdaptor

CParallelLightAdaptor::CParallelLightAdaptor()
{
  light = 0;
  name = "ParallelLight";
}

CParallelLightAdaptor::CParallelLightAdaptor(ParallelLight *l, CString n)
{
  light = l;
  name = n;
}

CParallelLightAdaptor::~CParallelLightAdaptor()
{
}


// CParallelLightAdaptor member functions

void CParallelLightAdaptor::Serialize(CArchive& ar) {
  CObject::Serialize(ar);

  if (ar.IsStoring()) {
    ar << name;
    ar << light->location;
    ar << light->direction;
    ar << light->attenuation;
    ar << light->color;
    ar << light->intensity;
  } else {
    light = new ParallelLight();
    ar >> name;
    ar >> light->location;
    ar >> light->direction;
    ar >> light->attenuation;
    ar >> light->color;
    ar >> light->intensity;
  }
}

bool CParallelLightAdaptor::EditObject() {
  CEditLightDialog dialog(light->location, light->direction, light->attenuation,
                           light->intensity, light->color, false, name);
  if (IDOK == dialog.DoModal()) {
    light->location = dialog.location;
    light->direction = dialog.direction;
    light->attenuation = dialog.attenuation;
    light->intensity = dialog.intensity;
    light->color = dialog.color;
    name = dialog.name;
    return true;
  }
  return false;
}
