#pragma once
#include "RenderView.h"
class IWorld;
class ApplicationBase
{
public:
	ApplicationBase();
	virtual ~ApplicationBase();


	bool Init(int argc, char** argv);
	
	void	ReadSettings();
	virtual void Run();
protected:
	virtual bool CreateAppWindow();
	virtual void OnInit();
	virtual void SetupScene();
	virtual void OnEndInit();
	virtual void PreUpdate();
	virtual void OnUpdate();


protected:
	int m_argc;
	char** m_argv;
	IWorld* m_pWorld;
	stRenderViewInfo m_RenderViewInfo;
};

