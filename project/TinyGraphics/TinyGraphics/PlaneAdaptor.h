#pragma once

#include "Kernel/Plane.h"
#include "Object3DAdaptor.h"

// CPlaneAdaptor command target

class CPlaneAdaptor : public CObject3DAdaptor
{
  DECLARE_SERIAL(CPlaneAdaptor)
public:
	CPlaneAdaptor();
  CPlaneAdaptor(TinyGraphics::Plane *plane, CString name);
	virtual ~CPlaneAdaptor();

  void Serialize(CArchive& ar);

  TinyGraphics::Plane *GetObject3D() {
    return plane;
  }

  bool EditObject();

protected:
  TinyGraphics::Plane *plane;
};
