#pragma once

#include "Kernel/PointLight.h"
#include "LightAdaptor.h"

// CPointLightAdaptor command target

class CPointLightAdaptor : public CLightAdaptor
{
  DECLARE_SERIAL(CPointLightAdaptor)
public:
	CPointLightAdaptor();
  CPointLightAdaptor(TinyGraphics::PointLight *light, CString name);
	virtual ~CPointLightAdaptor();

  void Serialize(CArchive& ar);

  TinyGraphics::PointLight *GetLight() {
    return light;
  }

  bool EditObject();

protected:
  TinyGraphics::PointLight *light;
};
