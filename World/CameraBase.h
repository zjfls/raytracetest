#pragma once
#include "ModuleBase.h"
#include "Matrix44.h"
#include "IListenerSubject.h"

//class IRender;
class IWorldObj;
//class IRenderTarget;
class WORLD_API CameraBase :
	public ModuleBase,public IListenerSubject
{
public:
	CameraBase();
	virtual ~CameraBase();
	virtual void Update(std::shared_ptr<ModuleBase> pModule);
	virtual void OnLateUpdate(std::shared_ptr<ModuleBase> pModule);
	virtual void Render(std::shared_ptr<CameraBase> pCamera);
	//IRender* m_pRender;
	//IRenderTarget* m_pRenderTarget;
	virtual shared_ptr<ModuleBase> Clone();


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
public:
	Matrix44 m_MatView;
	Matrix44 m_MatProj;
	Matrix44 m_MatViewProj;
	Matrix44 m_MatInverseView;
};

