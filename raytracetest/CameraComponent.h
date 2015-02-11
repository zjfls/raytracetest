#pragma once
#include "ObjComponent.h"

class Camera;
class CameraComponent :
	public ObjComponent
{
public:
	CameraComponent();
	~CameraComponent();
	CameraComponent(Camera* m_pCamera);
	Camera* m_pCamera;
};

