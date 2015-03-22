#pragma once
#include "RenderView.h"
class IWorld;
class ApplicationBase
{
public:
	ApplicationBase();
	virtual ~ApplicationBase();


	bool Init(int argc, char** argv);
	
	virtual void SetupScene();
	virtual void OnEndInit();
	virtual void PreUpdate();
	virtual void OnUpdate();
	virtual void Run();
protected:
	virtual bool CreateAppWindow();
	virtual void OnInit();


protected:
	int m_argc;
	char** m_argv;
	IWorld* m_pWorld;
	stRenderViewInfo m_RenderViewInfo;
};

