#pragma once
#include "ApplicationBase.h"
#include "windows.h"
class SimpleGLApplication :
	public ApplicationBase, public Singleton<SimpleGLApplication>
{
public:
	SimpleGLApplication();
	virtual ~SimpleGLApplication();

	virtual void OnInit();
	virtual void SetupScene();
	virtual void OnEndInit();
	virtual void Run();
private:
	void GlWindow(int width, int height);
	static void RenderScene();
};

