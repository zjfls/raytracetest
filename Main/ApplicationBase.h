#pragma once
#include "RenderView.h"
namespace ZG
{
	class IWorld;
	class RenderView;
	class MAIN_API ApplicationBase :public GameObjectBase
	{
	public:
		ApplicationBase();
		virtual ~ApplicationBase();


		bool Init(int argc, char** argv);

		void	ReadSettings();
		virtual void Run();
		virtual void OnClose();
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
		stRenderViewInfo m_RenderViewInfo;
		RenderView* m_pRenderView;
	public:
		SmartPointer<IWorld> m_pWorld;
	};
}
