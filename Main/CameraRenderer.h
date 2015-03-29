#pragma once
#include "IListener.h"
#include "RasterRender.h"
#include "IRenderTarget.h"
#include "IWorld.h"
class CameraRenderer :
	public IListener
{
public:
	CameraRenderer();
	virtual ~CameraRenderer();


	virtual void OnNotify(string msg, IListenerSubject* pSubject);
private:
	void Render(CameraBase* pCamera);
	void UpdateMatrix(CameraBase* pCamera);
public:
	RasterRender*	m_pRender;
	IRenderTarget*	m_pTarget;
	IWorld*			m_pWorld;
};

