#pragma once

#include "Kernel/Cylinder.h"
#include "Object3DAdaptor.h"

// CCylinderAdaptor command target

class CCylinderAdaptor : public CObject3DAdaptor
{
  DECLARE_SERIAL(CCylinderAdaptor)
public:
	CCylinderAdaptor();
  CCylinderAdaptor(TinyGraphics::Cylinder *cylinder, CString name);
	virtual ~CCylinderAdaptor();

  void Serialize(CArchive& ar);

  TinyGraphics::Cylinder *GetObject3D() {
    return cylinder;
  }

  bool EditObject();

protected:
  TinyGraphics::Cylinder *cylinder;
};
