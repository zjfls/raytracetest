#pragma once
class Camera;
class IWorld;
class IRender
{
public:
	IRender();
	virtual ~IRender();


	virtual int Render(Camera* pCammera, IWorld* pWorld) = 0;
};

