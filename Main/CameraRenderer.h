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


	virtual void OnNotify(string msg, shared_ptr<IListenerSubject> pSubject);
private:
	void Render(shared_ptr<CameraBase> pCamera);
	void UpdateMatrix(shared_ptr<CameraBase> pCamera);
public:
	RasterRender*	m_pRender;
	IRenderTarget*	m_pTarget;
	std::weak_ptr<IWorld>			m_pWorld;
	bool			m_bClearColor;
	bool			m_bClearDepth;
	GameColor			m_clrColr;
	float			m_fDepth;
	//
	RenderTargetGroup	m_pTargetGroup;
	//
	bool			m_bActive;
};

