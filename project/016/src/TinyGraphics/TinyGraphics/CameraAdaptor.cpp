// CameraAdaptor.cpp : implementation file
//

#include "stdafx.h"
#include "TinyGraphics.h"

#include "Kernel/Position.h"

#include "EditCameraDialog.h"
#include "Utilities.h"

#include "CameraAdaptor.h"

using namespace TinyGraphics;

IMPLEMENT_SERIAL(CCameraAdaptor, CObject, TG_VERSION + 1)

// CCameraAdaptor

CCameraAdaptor::CCameraAdaptor()
{
  parallelCamera = 0;
  perspectiveCamera = 0;
  is_parallel = 0;
}

CCameraAdaptor::CCameraAdaptor(ParallelCamera *c1, PerspectiveCamera *c2, bool p)
{
  parallelCamera = c1;
  perspectiveCamera = c2;
  is_parallel = p;
}

CCameraAdaptor::~CCameraAdaptor()
{
}

// CCameraAdaptor member functions

void CCameraAdaptor::Serialize(CArchive& ar)
{
  CObject::Serialize(ar);

  if (ar.IsStoring()) {
    ar << parallelCamera->get_position();
    ar << parallelCamera->get_project_direction();
    real w, h;
    parallelCamera->get_vpw(w, h);
    ar << w << h;
   
    ar << perspectiveCamera->get_position();
    ar << perspectiveCamera->get_project_direction();
    ar << perspectiveCamera->get_cop_distance();
    perspectiveCamera->get_vpw(w, h);
    ar << w << h;

    ar << is_parallel;
  } else {
    parallelCamera = new ParallelCamera();
    perspectiveCamera = new PerspectiveCamera();

    Position pos;  Vector3D proj_dir;
    real w, h; real cop_dist;
    ar >> pos;
    parallelCamera->set_position(pos);
    ar >> proj_dir;
    parallelCamera->set_project_direction(proj_dir);
    ar >> w >> h;
    parallelCamera->set_vpw(w, h);
   
    ar >> pos;
    perspectiveCamera->set_position(pos);
    ar >> proj_dir;
    perspectiveCamera->set_project_direction(proj_dir);
    ar >> cop_dist;
    perspectiveCamera->set_cop_distance(cop_dist);
    ar >> w >> h;
    perspectiveCamera->set_vpw(w, h);
    ar >> is_parallel;
  }
}


bool CCameraAdaptor::EditObject() {
  CEditCameraDialog dialog(parallelCamera, perspectiveCamera, is_parallel);

  if (IDOK == dialog.DoModal()) {    
    parallelCamera->set_position(Position(dialog.location[0], dialog.vf[0], dialog.vup[0]));
    parallelCamera->set_project_direction(dialog.pd[0]);
    parallelCamera->set_vpw(dialog.vpw[0], dialog.vpw[0] * dialog.ar[0]);

    perspectiveCamera->set_cop_distance(dialog.cop.to_vec3d().norm());
    perspectiveCamera->set_position(Position(dialog.location[1], dialog.vf[1], dialog.vup[1]));
    perspectiveCamera->set_project_direction(dialog.pd[1]);
    perspectiveCamera->set_vpw(dialog.vpw[1], dialog.vpw[1] * dialog.ar[1]);

    is_parallel = dialog.is_parallel;

    return true;
  }

  return false;
}
