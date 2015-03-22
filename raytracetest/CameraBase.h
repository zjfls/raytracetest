#pragma once
#include "ModuleBase.h"

class IRender;
class IWorldObj;
class IRenderTarget;
class CameraBase :
	public ModuleBase
{
public:
	CameraBase();
	virtual ~CameraBase();
	virtual void Update();
	virtual void OnLateUpdate();
	virtual void Render();
	IRender* m_pRender;
	IRenderTarget* m_pRenderTarget;

	float m_fVertFov;
	float m_fHorzFov;
};

