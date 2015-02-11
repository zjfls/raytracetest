#pragma once
#include "ModuleBase.h"

class IRender;
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
};

