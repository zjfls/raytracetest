#include "stdafx.h"
#include "ShaderAssetLoader.h"
#include "ShaderAsset.h"
#include "AssetManager.h"
#include "ResourceManager.h"
#include "VertexShader.h"
#include "FragShader.h"
//#include "d3d9.h"
//#include "d3dx9.h"

VertexShaderAssetLoader::VertexShaderAssetLoader()
{
}


VertexShaderAssetLoader::~VertexShaderAssetLoader()
{
}


IAsset* VertexShaderAssetLoader::Load(string path, void* pArg /*= nullptr*/)
{
	VertexShaderAsset* pAsset = new VertexShaderAsset();
	pAsset->m_strPath = path;
	shared_ptr<VertexShader> pVSResource = nullptr;
	if (ResourceManager<VertexShader>::GetInstance()->GetResource(path) != nullptr)
	{
		pVSResource = ResourceManager<VertexShader>::GetInstance()->GetResource(path);
		m_pAsset->AddResource(path, pVSResource);
		return m_pAsset;
	}
	m_pAsset = pAsset;
	FILE* fp;
	errno_t eOpen = fopen_s(&fp, path.c_str(), "rb");
	if (0 != eOpen)
	{
		std::cout << "open file:" << path.c_str() << std::endl;
		return nullptr;
	}
	int startPos = ftell(fp);
	fseek(fp, 0, SEEK_END); //定位到文件末 
	unsigned int nLength = ftell(fp); //文件长度
	fseek(fp, 0, startPos);
	char* pCode = new char[nLength + 1];
	fread(pCode, nLength,1, fp);
	pCode[nLength] = 0;
	//std::cout << pCode << std::endl;


	pVSResource = ResourceManager<VertexShader>::GetInstance()->CreateResource<VertexShader>(path);
	pVSResource->m_pCodeBuffer = pCode;
	m_pAsset->AddResource(path, pVSResource);
	return m_pAsset;

	//IDirect3DVertexShader9* pVertexShader;
	//LPD3DXCONSTANTTABLE		pVCT;
	//LPD3DXBUFFER pdxCode;
	//LPD3DXBUFFER pError;
	//if (D3DXCompileShader(pCode, nLength, NULL, NULL, "vMain", "vs_3_0", D3DXSHADER_DEBUG, &pdxCode, &pError, &pVCT) != D3D_OK)
	//{
	//	std::cout << "compile vertex shader failed" << std::endl;
	//	std::cout << (char*)pError->GetBufferPointer() << std::endl;
	//	//return E_FAIL;
	//}
}

//
FragShaderAssetLoader::FragShaderAssetLoader()
{

}

FragShaderAssetLoader::~FragShaderAssetLoader()
{

}

IAsset* FragShaderAssetLoader::Load(string path, void* pArg /*= nullptr*/)
{
	FragShaderAsset* pAsset = new FragShaderAsset();
	pAsset->m_strPath = path;
	shared_ptr<FragShader> pFSResource = nullptr;
	if (ResourceManager<FragShader>::GetInstance()->GetResource(path) != nullptr)
	{
		pFSResource = ResourceManager<FragShader>::GetInstance()->GetResource(path);
		m_pAsset->AddResource(path, pFSResource);
		return m_pAsset;
	}
	m_pAsset = pAsset;
	FILE* fp;
	errno_t eOpen = fopen_s(&fp, path.c_str(), "rb");
	if (0 != eOpen)
	{
		std::cout << "open file:" << path.c_str() << std::endl;
		return nullptr;
	}
	int startPos = ftell(fp);
	fseek(fp, 0, SEEK_END); //定位到文件末 
	unsigned int nLength = ftell(fp); //文件长度
	fseek(fp, 0, startPos);
	char* pCode = new char[nLength + 1];
	fread(pCode, nLength, 1, fp);
	pCode[nLength] = 0;
	//std::cout << pCode << std::endl;


	pFSResource = ResourceManager<FragShader>::GetInstance()->CreateResource<FragShader>(path);
	pFSResource->m_pCodeBuffer = pCode;
	m_pAsset->AddResource(path, pFSResource);
	return m_pAsset;

	//IDirect3DVertexShader9* pVertexShader;
	//LPD3DXCONSTANTTABLE		pVCT;
	//LPD3DXBUFFER pdxCode;
	//LPD3DXBUFFER pError;
	//if (D3DXCompileShader(pCode, nLength, NULL, NULL, "vMain", "vs_3_0", D3DXSHADER_DEBUG, &pdxCode, &pError, &pVCT) != D3D_OK)
	//{
	//	std::cout << "compile vertex shader failed" << std::endl;
	//	std::cout << (char*)pError->GetBufferPointer() << std::endl;
	//	//return E_FAIL;
	//}
}
