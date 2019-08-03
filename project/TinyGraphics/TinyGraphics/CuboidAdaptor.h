#pragma once

#include "Kernel/Cuboid.h"
#include "Object3DAdaptor.h"

// CCuboidAdaptor command target

class CCuboidAdaptor : public CObject3DAdaptor
{
  DECLARE_SERIAL(CCuboidAdaptor)
public:
	CCuboidAdaptor();
  CCuboidAdaptor(TinyGraphics::Cuboid *cuboid, CString name);
	virtual ~CCuboidAdaptor();

  void Serialize(CArchive& ar);

  TinyGraphics::Cuboid *GetObject3D() {
    return cuboid;
  }

  bool EditObject();

protected:
  TinyGraphics::Cuboid *cuboid;
};
