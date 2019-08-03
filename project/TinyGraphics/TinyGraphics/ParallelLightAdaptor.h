#pragma once

#include "Kernel/ParallelLight.h"
#include "LightAdaptor.h"

// CParallelLightAdaptor command target

class CParallelLightAdaptor : public CLightAdaptor
{
  DECLARE_SERIAL(CParallelLightAdaptor)
public:
	CParallelLightAdaptor();
  CParallelLightAdaptor(TinyGraphics::ParallelLight *light, CString name);
	virtual ~CParallelLightAdaptor();

  void Serialize(CArchive& ar);

  TinyGraphics::ParallelLight *GetLight() {
    return light;
  }

  bool EditObject();

protected:
  TinyGraphics::ParallelLight *light;
};
