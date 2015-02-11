#pragma once
class CameraBase;
class IWorld;
class IRender
{
public:
	IRender();
	virtual ~IRender();


	virtual int Render(CameraBase* pCammera, IWorld* pWorld) = 0;
};

