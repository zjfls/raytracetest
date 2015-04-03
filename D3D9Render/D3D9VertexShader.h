#pragma once
#include "HardwareVertexShader.h"
#include "d3d9.h"
#include "d3dx9.h"
struct IDirect3DVertexShader9;
class D3D9VertexShader :
	public HardwareVertexShader
{
public:
	D3D9VertexShader();
	virtual ~D3D9VertexShader();
	virtual bool SetBool(string strName, const bool bValue);
	virtual bool SetFloat(string strName, const float fValue);
	virtual bool SetInt(string strName, const float nValue);
	virtual bool SetVector(string strName, const Vector4& nValue);
	virtual bool SetMatrix(string strName, const Matrix44& nValue);
	


	IDirect3DVertexShader9* m_pVertexShader;
	ID3DXConstantTable*	m_pConstantTable;



	IDirect3DDevice9* m_pDevice;
};

