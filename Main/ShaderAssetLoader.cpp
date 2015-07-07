#include "stdafx.h"
#include "ShaderAssetLoader.h"
#include "ShaderAsset.h"
#include "AssetManager.h"
#include "ResourceManager.h"
#include "VertexShader.h"
#include "FragShader.h"
#include "ShaderGenerator.h"
//#include "d3d9.h"
//#include "d3dx9.h"

VertexShaderAssetLoader::VertexShaderAssetLoader()
{
}


VertexShaderAssetLoader::~VertexShaderAssetLoader()
{
}


IAsset* VertexShaderAssetLoader::Load(std::string path, void* pArg /*= nullptr*/)
{
	VertexShaderAsset* pAsset = new VertexShaderAsset();
	pAsset->m_strPath = path;
	SmartPointer<VertexShader> pVSResource = nullptr;
	if (ResourceManager<VertexShader>::GetInstance()->GetResource(path) != nullptr)
	{
		pVSResource = ResourceManager<VertexShader>::GetInstance()->GetResource(path);
		m_pAsset->AddResource(path, pVSResource.get());
		return m_pAsset;
	}
	m_pAsset = pAsset;
	FILE* fp;
	errno_t eOpen = fopen_s(&fp, path.c_str(), "rb");
	if (0 != eOpen)
	{
		std::cout << "open file:" << path.c_str()<<"failed!!!" << std::endl;
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
	m_pAsset->AddResource(path, pVSResource.get());
	fclose(fp);
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

IAsset* FragShaderAssetLoader::Load(std::string path, void* pArg /*= nullptr*/)
{
	FragShaderAsset* pAsset = new FragShaderAsset();
	pAsset->m_strPath = path;
	SmartPointer<FragShader> pFSResource = nullptr;
	if (ResourceManager<FragShader>::GetInstance()->GetResource(path) != nullptr)
	{
		pFSResource = ResourceManager<FragShader>::GetInstance()->GetResource(path);
		m_pAsset->AddResource(path, pFSResource.get());
		return m_pAsset;
	}
	m_pAsset = pAsset;
	FILE* fp;
	errno_t eOpen = fopen_s(&fp, path.c_str(), "rb");
	if (0 != eOpen)
	{
		std::cout << "open file:" << path.c_str()<<" failed!!!" << std::endl;
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
	m_pAsset->AddResource(path, pFSResource.get());
	fclose(fp);
	ShaderGenerator::PreProcessShader(pCode, nLength + 1, pFSResource->m_mapEngineParam);
	//
	//char t[] = "a,b,c,de";
	//const char *split = ",";
	//char *p = NULL, *pNext = NULL;
	//p = strtok_s(t, split, &pNext);
	//CString R = L"";
	//while (p != NULL){
	//	R += char_to_cstring(p);
	//	R += L"\r\n";
	//	R += L"-----------------";
	//	R += L"\r\n";
	//	p = strtok_s(NULL, split, &pNext);
	//}
	//自动生成代码的时候防止重复生成
	//char* pTempCode = new char[nLength + 1];
	//memcpy(pTempCode, pCode, nLength + 1);
	//const char* d = "\n";
	//char* pNext;
	//char* p = strtok_s(pTempCode, d, &pNext);
	//char* pComment;
	//while (p != nullptr)
	//{
	//	std::cout << p << std::endl;
	//	pComment = strstr(p, "//");

	//	if (pComment != nullptr)
	//	{
	//		*pComment = 0;
	//		pComment = nullptr;
	//		//
	//		const char* pKey = strstr(p, "VIEW_POS");
	//		if (pKey != nullptr)
	//		{
	//			pFSResource->m_vecEngineParam.push_back("VIEW_POS");
	//		}
	//	}


	//	//
	//	//
	//	p = strtok_s(nullptr, d, &pNext);
	//}
	
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
