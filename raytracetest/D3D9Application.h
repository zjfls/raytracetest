#pragma once
#include "ApplicationBase.h"
#include "windows.h"
class D3D9Application :
	public ApplicationBase, public Singleton < D3D9Application >
{
public:
	D3D9Application();
	virtual ~D3D9Application();

	
	virtual void SetupScene();
	virtual void OnEndInit();
	virtual void Run();
	void		CleanUp();
protected:
	virtual void OnInit();
	virtual bool CreateAppWindow();
private:
	static long __stdcall WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp);
};

