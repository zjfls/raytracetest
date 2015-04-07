#include "stdafx.h"
#include "D3D9VertexShader.h"
#include "d3d9.h"
#include "Matrix44.h"


D3D9VertexShader::D3D9VertexShader()
	:m_pVertexShader(nullptr)
	, m_pConstantTable(nullptr)
{
}


D3D9VertexShader::~D3D9VertexShader()
{
	SAFE_RELEASE(m_pConstantTable);
	SAFE_RELEASE(m_pVertexShader);
}

bool D3D9VertexShader::SetBool(string strName, const bool bValue)
{
	HRESULT hr = m_pConstantTable->SetBool(m_pDevice,strName.c_str(), bValue);
	if (hr != D3D_OK)
	{
		return false;
	}
	return true;
}

bool D3D9VertexShader::SetFloat(string strName, const float fValue)
{
	HRESULT hr = m_pConstantTable->SetFloat(m_pDevice, strName.c_str(), fValue);
	if (hr != D3D_OK)
	{
		return false;
	}
	return true;
}

bool D3D9VertexShader::SetInt(string strName, const float nValue)
{
	HRESULT hr = m_pConstantTable->SetInt(m_pDevice, strName.c_str(), nValue);
	if (hr != D3D_OK)
	{
		return false;
	}
	return true;
}

bool D3D9VertexShader::SetVector(string strName, const Vector4& vecValue)
{
	HRESULT hr = m_pConstantTable->SetVector(m_pDevice, strName.c_str(), (const D3DXVECTOR4*)&vecValue);
	if (hr != D3D_OK)
	{
		return false;
	}
	return true;
}

bool D3D9VertexShader::SetMatrix(string strName, const Matrix44& matValue)
{
	D3DXMATRIX mat;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4;++j)
		{
			mat.m[i][j] = matValue.M[i][j];
		}
	}
	HRESULT hr = m_pConstantTable->SetMatrix(m_pDevice, strName.c_str(), &mat);
	if (hr != D3D_OK)
	{
		return false;
	}
	return true;
}

bool D3D9VertexShader::SetFloatArray(string strName, const float* pData, unsigned int nLenght)
{
	HRESULT hr = m_pConstantTable->SetFloatArray(m_pDevice, strName.c_str(), (const float*)&pData, nLenght);
	if (hr != D3D_OK)
	{
		return false;
	}
	return true;
}

