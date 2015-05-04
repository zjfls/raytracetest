#pragma once
#include "ApplicationBase.h"
#include "windows.h"
#include "Singleton.h"
class IWorldObj;
class MAIN_API D3D9Application :
	public ApplicationBase, public Singleton < D3D9Application >
{
public:
	D3D9Application();
	virtual ~D3D9Application();

	

	virtual void Run();
	void		CleanUp();
protected:
	virtual void OnInit();
	virtual void SetupScene();
	virtual void OnEndInit();
	virtual bool CreateAppWindow();
private:
	static long __stdcall WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp);
	shared_ptr<IWorldObj>				m_pTargetObj;
};

extern template class MAIN_API  Singleton < D3D9Application >;