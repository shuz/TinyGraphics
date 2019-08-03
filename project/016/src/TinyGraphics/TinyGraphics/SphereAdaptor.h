#pragma once

#include "Kernel/Sphere.h"
#include "Object3DAdaptor.h"

// CSphereAdaptor command target

class CSphereAdaptor : public CObject3DAdaptor
{
  DECLARE_SERIAL(CSphereAdaptor)
public:
	CSphereAdaptor();
  CSphereAdaptor(TinyGraphics::Sphere *sphere, CString name);
	virtual ~CSphereAdaptor();

  void Serialize(CArchive& ar);

  TinyGraphics::Sphere *GetObject3D() {
    return sphere;
  }

  bool EditObject();

protected:
  TinyGraphics::Sphere *sphere;
};
