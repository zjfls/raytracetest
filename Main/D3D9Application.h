#pragma once
#include "ApplicationBase.h"
#include "windows.h"
#include "Singleton.h"

namespace ZG
{
	class IWorldObj;
	class MAIN_API D3D9Application :
		public ApplicationBase/*, public Singleton < D3D9Application >*/
	{
	public:
		D3D9Application();
		virtual ~D3D9Application();



		virtual void Run();
		//void		CleanUp();
		static D3D9Application* theApp;
	protected:
		virtual void OnInit();
		virtual void SetupScene();
		virtual void OnEndInit();
		virtual bool CreateAppWindow();
		void OnClose() override;
	private:
		static long __stdcall WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp);
		SmartPointer<IWorldObj>				m_pTargetObj;
	};

	extern template class MAIN_API  Singleton < D3D9Application > ;
}
