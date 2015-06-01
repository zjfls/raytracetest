#pragma once
#include "Vector2.h"
class CameraBase;
class MAIN_API PickUtil
{
public:
	PickUtil();
	~PickUtil();


	static Vector3 ScreenPosToWorldPos(Vector2& screenPos,float fDistToCamera,SmartPointer<CameraBase> pCamera,int nScreenWidth,int nScreenHeight);
	static Vector2 WorldPosToScreenPos(Vector3& worldPos,SmartPointer<CameraBase> pCamera);
};

