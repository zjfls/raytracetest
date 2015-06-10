#pragma once
#include "ApplicationBase.h"
namespace ZG
{
	class RayTraceCamera;
	class MAIN_API RayTraceApplication :public ApplicationBase, public Singleton < RayTraceApplication >
	{
	public:
		~RayTraceApplication();

		virtual void OnInit();
		virtual void SetupScene();
		virtual void OnEndInit();
		//virtual void PreUpdate();
		//virtual void OnUpdate();
	protected:
		RayTraceApplication();
		friend class Singleton < RayTraceApplication > ;
	private:
		SmartPointer<RayTraceCamera> m_pCamera;
	};

}