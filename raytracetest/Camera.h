#pragma once
#include "CameraBase.h"
#include "Matrix44.h"
class Camera :
	public CameraBase
{
public:
	Camera();
	~Camera();
	virtual void Update();



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

