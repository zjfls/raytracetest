#pragma once
#include "IListener.h"
#include "RasterRender.h"
#include "IRenderTarget.h"
#include "IWorld.h"
#include "Color.h"
#include "RenderTargetGroup.h"
class MAIN_API CameraRenderer :
	public IListener
{
public:
	CameraRenderer();
	virtual ~CameraRenderer();


	virtual void OnNotify(string msg, IListenerSubject* pSubject);
private:
	void Render(SmartPointer<CameraBase> pCamera);
	void UpdateMatrix(SmartPointer<CameraBase> pCamera);
public:
	RasterRender*		m_pRender;
	IRenderTarget*		m_pTarget;
	IWorld*				m_pWorld;
	bool				m_bClearColor;
	bool				m_bClearDepth;
	GameColor			m_clrColr;
	float				m_fDepth;

	//
	bool				m_bActive;
};

