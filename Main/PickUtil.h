#pragma once
#include "Vector2.h"
class CameraBase;
class MAIN_API PickUtil
{
public:
	PickUtil();
	~PickUtil();


	static Vector3 ScreenPosToWorldPos(Vector2& screenPos,float fDistToCamera,shared_ptr<CameraBase> pCamera,int nScreenWidth,int nScreenHeight);
	static Vector2 WorldPosToScreenPos(Vector3& worldPos,shared_ptr<CameraBase> pCamera);
};

