#pragma once

#include "Kernel/World3D.h"

// CWorldAdaptor command target

class CWorldAdaptor : public CObject
{
  DECLARE_SERIAL(CWorldAdaptor)
public:
  CWorldAdaptor();
  CWorldAdaptor(TinyGraphics::World3D *world);
	virtual ~CWorldAdaptor();

  virtual void Serialize(CArchive& ar);

  bool EditObject();

public:
  TinyGraphics::World3D *world;
  int m_nextObjNum;
};
