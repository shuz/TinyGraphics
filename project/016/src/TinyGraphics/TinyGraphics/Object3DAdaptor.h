#pragma once

#include "Kernel/Object3D.h"

// CObject3DAdaptor command target

class CObject3DAdaptor : public CObject
{
public:
	CObject3DAdaptor();
	virtual ~CObject3DAdaptor();

  virtual TinyGraphics::Object3D *GetObject3D() = 0;
  virtual bool EditObject() = 0;

public:
  CString name;
};
