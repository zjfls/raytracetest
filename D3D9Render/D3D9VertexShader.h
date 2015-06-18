#pragma once
#include "HardwareVertexShader.h"
#include "d3d9.h"
#include "d3dx9.h"
struct IDirect3DVertexShader9;


namespace ZG
{
	class D3D9VertexShader :
		public HardwareVertexShader
	{
	public:
		D3D9VertexShader();
		virtual ~D3D9VertexShader();
		virtual bool SetBool(string strName, const bool bValue);
		virtual bool SetFloat(string strName, const float fValue);
		virtual bool SetInt(string strName, const int nValue);
		virtual bool SetVector(string strName, const Vector4& nValue);
		virtual bool SetMatrix(string strName, const Matrix44& nValue);
		virtual bool SetFloatArray(string strName, const float* pData, unsigned int nLenght);
		bool			SetMatrixArray(string strName, const Matrix44* pMat, unsigned int nSize) override;

		IDirect3DVertexShader9* m_pVertexShader;
		ID3DXConstantTable*	m_pConstantTable;



		IDirect3DDevice9* m_pDevice;
	};
}


