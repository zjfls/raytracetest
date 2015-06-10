#pragma once
#include "ModuleBase.h"
#include "Matrix44.h"
#include "IListenerSubject.h"
#include "Color.h"

//class IRenderTarget;
;
namespace ZG
{
	class CameraBase;
	struct WORLD_API CameraRenderEvent
	{
		SmartPointer<CameraBase> m_pTargetCamera;
	};
	class IWorld;
	class IRenderTarget;
	//class IRender;
	class IWorldObj;
	class WORLD_API CameraBase :
		public ModuleBase
	{
	public:
		CameraBase();
		virtual ~CameraBase();
		virtual void Update();
		virtual void OnLateUpdate();
		virtual void Render();
		//IRender* m_pRender;
		//IRenderTarget* m_pRenderTarget;
		virtual SmartPointer<ModuleBase> Clone();
		//void	RegistRender(SmartPointer<IRender> pRender);

		Matrix44 GetViewMatrix() const{ return m_MatView; };
		Matrix44 GetProjMatrix() const{ return m_MatProj; };
		Matrix44 GetViewProjMatrix() const{ return m_MatViewProj; };
		Matrix44 GetInverseViewProjMatrix() const{ return m_MatInverseView; };
	private:
		void UpdateMatrix();
	public:
		float m_fFovy;
		float m_fAspect;
		float m_fNear;
		float m_fFar;
		//
		SmartPointer<IRenderTarget>	m_pTarget;
		SmartPointer<IWorld>	m_pWorld;
		bool				m_bClearColor;
		bool				m_bClearDepth;
		GameColor			m_clrColr;
		float				m_fDepth;
		bool				m_bHDR;
	public:
		Matrix44 m_MatView;
		Matrix44 m_MatProj;
		Matrix44 m_MatViewProj;
		Matrix44 m_MatInverseView;
	};
}


