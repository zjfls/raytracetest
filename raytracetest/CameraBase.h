#pragma once
#include "ModuleBase.h"

class IRender;
class IWorldObj;
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


	float m_fVertFov;
	float m_fHorzFov;
};

