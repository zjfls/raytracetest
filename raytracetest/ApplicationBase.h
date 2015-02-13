#pragma once

class IWorld;
class ApplicationBase
{
public:
	ApplicationBase();
	virtual ~ApplicationBase();


	bool Init();
	virtual void OnInit();
	virtual void OnSetupScene();
	virtual void OnEndInit();
	virtual void PreUpdate();
	virtual void OnUpdate();



	IWorld* m_pWorld;
};

