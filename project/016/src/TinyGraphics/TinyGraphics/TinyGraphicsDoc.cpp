// TinyGraphicsDoc.cpp : implementation of the CTinyGraphicsDoc class
//

#include "stdafx.h"
#include "TinyGraphics.h"

#include "TinyGraphicsDoc.h"

#include "Object3DAdaptor.h"

#include "Kernel/World3D.h"

using namespace TinyGraphics;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTinyGraphicsDoc

IMPLEMENT_DYNCREATE(CTinyGraphicsDoc, CDocument)

BEGIN_MESSAGE_MAP(CTinyGraphicsDoc, CDocument)
END_MESSAGE_MAP()


// CTinyGraphicsDoc construction/destruction

CTinyGraphicsDoc::CTinyGraphicsDoc()
{
	// TODO: add one-time construction code here
  m_pCamera = 0;
  m_world = 0;
  m_worldAdaptor.world = m_world;
  m_reflectDepth = 2;
  m_refractDepth = 3;
  m_useMaterial = false;
}

CTinyGraphicsDoc::~CTinyGraphicsDoc()
{
  delete m_pCamera;
  delete m_world;
  ClearObjectAdaptors();
  ClearLightAdaptors();
}

BOOL CTinyGraphicsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
  ResetDoc();

	return TRUE;
}

// CTinyGraphicsDoc serialization

void CTinyGraphicsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
    ar << (long)m_objects.GetCount();
	  POSITION pos = m_objects.GetStartPosition();
    CObject3DAdaptor *adaptor;
    Object3D *object;
    while (pos != 0)
    {
      m_objects.GetNextAssoc(pos, object, adaptor);
      ar << adaptor;
    }

    ar << (long)m_lights.GetCount();
	  pos = m_lights.GetStartPosition();
    CLightAdaptor *ladaptor;
    Light *light;
    while (pos != 0)
    {
      m_lights.GetNextAssoc(pos, light, ladaptor);
      ar << ladaptor;
    }
    ar << m_pCamera;
    ar << m_reflectDepth;
    ar << m_refractDepth;
    ar << m_useMaterial;
	}
	else
	{
    int i;
    ResetDoc();

    long obj_num;
    ar >> obj_num;
    for (i = 0; i < obj_num; ++i) {
      CObject *adaptor;
      ar >> adaptor;
      AddObject((CObject3DAdaptor *)adaptor);
    }

    long lgt_num;
    ar >> lgt_num;
    for (i = 0; i < lgt_num; ++i) {
      CObject *adaptor;
      ar >> adaptor;
      AddLight((CLightAdaptor *)adaptor);
    }
    ar >> m_pCamera;
    ar >> m_reflectDepth;
    ar >> m_refractDepth;
    ar >> m_useMaterial;
  }
  m_worldAdaptor.Serialize(ar);
}


// CTinyGraphicsDoc diagnostics

#ifdef _DEBUG
void CTinyGraphicsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTinyGraphicsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTinyGraphicsDoc commands

void CTinyGraphicsDoc::AddObject(CObject3DAdaptor *adaptor)
{
  Object3D *object = adaptor->GetObject3D();
  m_objects[object] = adaptor;
  m_world->add(object);
}

void CTinyGraphicsDoc::RemoveObject(CObject3DAdaptor *adaptor)
{
  Object3D *object = adaptor->GetObject3D();
  m_objects.RemoveKey(object);
  m_world->remove(object);
  delete object;
}

CObject3DAdaptor *CTinyGraphicsDoc::LookupAdaptor(Object3D *obj)
{
  CObject3DAdaptor *adaptor;
  if (m_objects.Lookup(obj, adaptor))
    return adaptor;
  return 0;
}

void CTinyGraphicsDoc::ClearObjectAdaptors()
{
  POSITION pos = m_objects.GetStartPosition();
  CObject3DAdaptor *adaptor;
  Object3D *object;
  while (pos != 0)
  {
    m_objects.GetNextAssoc(pos, object, adaptor);
    delete adaptor;
  }
  m_objects.RemoveAll();
}

void CTinyGraphicsDoc::AddLight(CLightAdaptor *adaptor)
{
  Light *light = adaptor->GetLight();
  m_lights[light] = adaptor;
  m_world->add(light);
}

void CTinyGraphicsDoc::RemoveLight(CLightAdaptor *adaptor)
{
  Light *light = adaptor->GetLight();
  m_lights.RemoveKey(light);
  m_world->remove(light);
  delete light;
}

CLightAdaptor *CTinyGraphicsDoc::LookupAdaptor(Light *obj)
{
  CLightAdaptor *adaptor;
  if (m_lights.Lookup(obj, adaptor))
    return adaptor;
  return 0;
}

void CTinyGraphicsDoc::ClearLightAdaptors()
{
  POSITION pos = m_lights.GetStartPosition();
  CLightAdaptor *adaptor;
  Light *light;
  while (pos != 0)
  {
    m_lights.GetNextAssoc(pos, light, adaptor);
    delete adaptor;
  }
  m_lights.RemoveAll();
}

void CTinyGraphicsDoc::ResetDoc() {
  m_reflectDepth = 2;
  m_refractDepth = 3;
  m_useMaterial = false;

  delete m_pCamera;
  m_pCamera = 0;

  delete m_world;
  m_world = new World3D();
  m_worldAdaptor.world = m_world;

  ClearObjectAdaptors();
  ClearLightAdaptors();
}

