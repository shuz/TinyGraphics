#pragma once

#include "Kernel/Cone.h"
#include "Object3DAdaptor.h"

// CConeAdaptor command target

class CConeAdaptor : public CObject3DAdaptor
{
  DECLARE_SERIAL(CConeAdaptor)
public:
	CConeAdaptor();
  CConeAdaptor(TinyGraphics::Cone *cone, CString name);
	virtual ~CConeAdaptor();

  void Serialize(CArchive& ar);

  TinyGraphics::Cone *GetObject3D() {
    return cone;
  }

  bool EditObject();

protected:
  TinyGraphics::Cone *cone;
};
