#pragma once

#include "Kernel/ParallelCamera.h"
#include "Kernel/PerspectiveCamera.h"

// CCameraAdaptor command target

class CCameraAdaptor : public CObject
{
  DECLARE_SERIAL(CCameraAdaptor)
public:
  CCameraAdaptor();
  CCameraAdaptor(TinyGraphics::ParallelCamera *parallelCamera,
                 TinyGraphics::PerspectiveCamera *perspectiveCamera,
                 bool is_parallel);
	virtual ~CCameraAdaptor();

  virtual void Serialize(CArchive& ar);

  TinyGraphics::Camera *GetCamera() {
    if (is_parallel)
      return parallelCamera;
    return perspectiveCamera;
  }
  bool EditObject();

public:
  TinyGraphics::ParallelCamera *parallelCamera;
  TinyGraphics::PerspectiveCamera *perspectiveCamera;
  bool is_parallel;
};
