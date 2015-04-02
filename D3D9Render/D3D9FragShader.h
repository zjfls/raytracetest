#pragma once
#include "HardwareFragShader.h"
#include "d3d9.h"
#include "d3dx9.h"
struct IDirect3DPixelShader9;
class D3D9FragShader :
	public HardwareFragShader
{
public:
	D3D9FragShader();
	virtual ~D3D9FragShader();
	virtual bool SetBool(string strName, const bool bValue);
	virtual bool SetFloat(string strName, const float fValue);
	virtual bool SetInt(string strName, const float nValue);
	virtual bool SetVector(string strName, const Vector4& nValue);
	virtual bool SetMatrix(string strName, const Matrix44& nValue);

	//
	IDirect3DPixelShader9* m_pFragShader;
	ID3DXConstantTable*	m_pConstantTable;
	IDirect3DDevice9* m_pDevice;
};

