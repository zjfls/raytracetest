#pragma once
#include "ModuleBase.h"

class IRender;
class IWorldObj;
class IRenderTarget;
class CameraBase :
	public ModuleBase
{
public:
	CameraBase();
	virtual ~CameraBase();
	virtual void Update();
	virtual void OnLateUpdate();
	virtual void Render();
	IRender* m_pRender;
	IRenderTarget* m_pRenderTarget;

	float m_fVertFov;
	float m_fHorzFov;

	Matrix44 GetViewMatrix() const{ return m_MatView; };
	Matrix44 GetProjMatrix() const{ return m_MatProj; };
	Matrix44 GetViewProjMatrix() const{ return m_MatViewProj; };
	Matrix44 GetInverseViewProjMatrix() const{ return m_MatInverseViewProj; };
private:

	void UpdateMatrix();


	Matrix44 m_MatView;
	Matrix44 m_MatProj;
	Matrix44 m_MatViewProj;
	Matrix44 m_MatInverseViewProj;
};

