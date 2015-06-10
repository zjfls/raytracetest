#pragma once
#include "HardwareFragShader.h"
#include "d3d9.h"
#include "d3dx9.h"
struct IDirect3DPixelShader9;
namespace ZG
{
	class D3D9FragShader :
		public HardwareFragShader
	{
	public:
		D3D9FragShader();
		virtual ~D3D9FragShader();
		virtual bool SetBool(string strName, const bool bValue);
		virtual bool SetFloat(string strName, const float fValue);
		virtual bool SetInt(string strName, const int nValue);
		virtual bool SetVector(string strName, const Vector4& nValue);
		virtual bool SetMatrix(string strName, const Matrix44& nValue);
		virtual bool SetFloatArray(string strName, const float* pData, unsigned int nLenght);
		//
		IDirect3DPixelShader9* m_pFragShader;
		ID3DXConstantTable*	m_pConstantTable;
		IDirect3DDevice9* m_pDevice;
	};
}


