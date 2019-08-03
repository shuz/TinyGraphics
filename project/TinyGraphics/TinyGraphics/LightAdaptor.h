#pragma once

#include "Kernel/Light.h"

// CLightAdaptor command target

class CLightAdaptor : public CObject
{
public:
	CLightAdaptor();
	virtual ~CLightAdaptor();

  virtual TinyGraphics::Light *GetLight() = 0;
  virtual bool EditObject() = 0;

public:
  CString name;
};
