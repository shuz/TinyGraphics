// TinyGraphicsDoc.h : interface of the CTinyGraphicsDoc class
//


#pragma once

#include "Object3DAdaptor.h"
#include "LightAdaptor.h"
#include "CameraAdaptor.h"
#include "WorldAdaptor.h"

#include <afxtempl.h>

using namespace TinyGraphics;

class CTinyGraphicsDoc : public CDocument
{
protected: // create from serialization only
	CTinyGraphicsDoc();
	DECLARE_DYNCREATE(CTinyGraphicsDoc)

// Attributes
public:
  CWorldAdaptor m_worldAdaptor;
  World3D *m_world;
  CCameraAdaptor *m_pCamera;
  typedef CMap<Object3D *, Object3D *, CObject3DAdaptor *, CObject3DAdaptor *> ObjectContainer;
  ObjectContainer m_objects;
  typedef CMap<Light *, Light *, CLightAdaptor *, CLightAdaptor *> LightContainer;
  LightContainer m_lights;

  int m_reflectDepth, m_refractDepth;
  bool m_useMaterial;

// Operations
public:
  void AddObject(CObject3DAdaptor *obj);
  void RemoveObject(CObject3DAdaptor *obj);
  CObject3DAdaptor *LookupAdaptor(Object3D *obj);
  void ClearObjectAdaptors();

  void AddLight(CLightAdaptor *obj);
  void RemoveLight(CLightAdaptor *obj);
  CLightAdaptor *LookupAdaptor(Light *obj);
  void ClearLightAdaptors();

  void ResetDoc();

  int CTinyGraphicsDoc::GetNextObjNum() {
    return m_worldAdaptor.m_nextObjNum++;
  }

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CTinyGraphicsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};
