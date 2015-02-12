#pragma once
#include "Orientation.h"
#include "ModuleBase.h"
#include "Matrix33.h"
#include "Matrix44.h"

/////////////////////////////////////////////////
class Transform:public ModuleBase
{
public:
	Transform();
	~Transform();

	virtual void Update();
	Vector3	GetRight();
	Vector3 GetForward();
	Vector3	GetUp();
////////////////////////////////////////////////
	Point3D m_vecTranslate;
	Orientation m_Orientation;
	Vector3 m_vecScale;

public:
	//Matrix33	m_RotMatrixLocal;
	//Matrix33	m_RotMatrixParent;
	//Matrix33	m_RotMatrixWorld;
	Matrix44	m_TransformMatrixLocal;
	//Matrix44	m_TransformMatrixParent;
	Matrix44	m_TransformMatrixWorld;
	//is need to change
	bool m_bDirt;
	
};

