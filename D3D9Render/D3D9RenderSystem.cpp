#include "stdafx.h"
#include "d3d9.h"
#include "D3D9RenderSystem.h"
#include "D3D9Render.h"
#include "D3D9IndexBuffer.h"
#include "D3D9VertexBuffer.h"
#include "D3D9VertexShader.h"
#include "D3D9FragShader.h"

//#include "RenderView.h"
#include "D3D9RenderView.h"
#include "D3D9Texture2D.h"
#include "VertexShader.h"
#include "FragShader.h"
#include "IndexData.h"
#include "VertexData.h"
#include "Texture.h"
#include "D3D9RenderTarget.h"
#include "EnviromentSetting.h"
#include "DynamicVertexData.h"
#include "D3DDepthBuffer.h"
D3D9RenderSystem::D3D9RenderSystem()
	:m_pD3D(nullptr)
	, m_pD3DDevice(nullptr)
{
}


D3D9RenderSystem::~D3D9RenderSystem()
{
}


bool operator==(const std::vector<D3DVERTEXELEMENT9>& e1,const std::vector<D3DVERTEXELEMENT9>& e2)
{
	if (e1.size() != e2.size())
	{
		return false;
	}
	for (int i = 0; i < e1.size(); ++i)
	{
		if (e1[i].Method == e2[i].Method 
			&&e1[i].Offset == e2[i].Offset
			&&e1[i].Stream == e2[i].Stream
			&&e1[i].Type == e2[i].Type
			&&e1[i].Usage == e2[i].Usage
			&&e1[i].UsageIndex == e2[i].UsageIndex
			)
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool operator<(const std::vector<D3DVERTEXELEMENT9>& e1,const std::vector<D3DVERTEXELEMENT9>& e2)
{
	return true;
}

bool D3D9RenderSystem::InitRenderSystem( stRenderViewInfo& viewInfo)
{
	//return test(viewInfo);
	//return;
	if (nullptr == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		std::cout << "get d3d9 object failed!" << std::endl;
		return false;
	}
	D3DCAPS9 d3dcaps;
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dcaps);
	std::cout << "Device Caps VertexShaderConstant:" << d3dcaps.MaxVertexShaderConst << std::endl;
	//create device


	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferHeight = viewInfo.m_nHeight;
	d3dpp.BackBufferWidth = viewInfo.m_nWidth;
	d3dpp.BackBufferCount = 1;
	d3dpp.Windowed = viewInfo.m_bWindowed;
	d3dpp.SwapEffect = getSwapEffect(viewInfo.m_eSwapEffect);
	d3dpp.BackBufferFormat = getBufferFormat(viewInfo.m_eTargetFormt);
	d3dpp.EnableAutoDepthStencil = viewInfo.m_bDepth;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	d3dpp.hDeviceWindow = (HWND)viewInfo.m_windowID;
	if (viewInfo.m_bDepth == true)
	{
		d3dpp.AutoDepthStencilFormat =  getBufferFormat(viewInfo.m_eDepthFormt);
	}
	m_D3DPresentParamenter = d3dpp;

	HRESULT hr = 0;
	if (FAILED(hr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, HWND(viewInfo.m_windowID),
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		std::cout << "create device failed" << std::endl;
		return false;
	}
	//
	if (EnviromentSetting::GetInstance()->GetIntSetting("LinearLighting") == true)
	{
		m_pD3DDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, TRUE);
	}




	D3D9RenderView* pRenderView;
	IDirect3DSwapChain9* pSwapChain = nullptr;
	m_pD3DDevice->GetSwapChain(0, &pSwapChain);
	
	//m_SwapChains.push_back(pSwapChain);
	pRenderView = new D3D9RenderView;
	pRenderView->m_nIndex = 0;
	pRenderView->m_nWidth = d3dpp.BackBufferWidth;
	pRenderView->m_nHeight = d3dpp.BackBufferHeight;
	pRenderView->m_dpp = d3dpp;
	pRenderView->m_pSwapChain = pSwapChain;
	m_pDefaultRenderView = pRenderView;
	pRenderView->m_pD3DDevice = m_pD3DDevice;


	m_vecRenderTarget.push_back(pRenderView);
	D3DDepthBuffer* pBuffer = new D3DDepthBuffer;
	m_pD3DDevice->GetDepthStencilSurface(&pBuffer->m_pDepthSurface);
	m_vecDepthBuffer.push_back(pBuffer);
	pBuffer->m_nDepth = 24;
	pBuffer->m_nWidth = pRenderView->m_nWidth;
	pBuffer->m_nHeight = pRenderView->m_nHeight;
	pBuffer->m_pD3DDevice = m_pD3DDevice;

	pRenderView->m_DepthBuffer = pBuffer;
	//if (EnviromentSetting::GetInstance()->GetIntSetting("HDR") == true)
	//{
	//	pRenderView->CreateHdrTarget();
	//}


	//D3D9Manager::GetInstance()->m_pDefaultRender = new D3D9Render(RenderPathManager::GetInstance()->GetRenderPath(
	//	EnviromentSetting::GetInstance()->GetSetting("DefaultPath")));
	return true;
}

D3DSWAPEFFECT D3D9RenderSystem::getSwapEffect(const EBUFFSWARP eSwap)
{
	switch (eSwap)
	{
		case BSDISCARD:
		{
			return D3DSWAPEFFECT_DISCARD;
		}
		break;
		case BSFLIP:
		{
			return D3DSWAPEFFECT_FLIP;
		}
		break;
		case BSCOPY:
		{
			return D3DSWAPEFFECT_COPY;
		}
		break;
		case BSOVERLAY:
		{
			return D3DSWAPEFFECT_OVERLAY;
		}
		break;
		default:
		return D3DSWAPEFFECT_COPY;
		break;
	}
}

D3DFORMAT D3D9RenderSystem::getBufferFormat(const TARGETFORMAT eFormat)
{
	switch (eFormat)
	{
		case TFA2R10G10B10:
		{
			return D3DFMT_A2B10G10R10;
		}
		break;
		case TFA8R8G8B8:
		{
			return D3DFMT_A8R8G8B8;
		}
		break;
		case TFX8R8G8B8:
		{
			return D3DFMT_X8R8G8B8;
		}
		break;
		case TFA1R5G5B5:
		{
			return D3DFMT_A1R5G5B5;
		}
		break;
		case TFX1R5B5G5:
		{
			return D3DFMT_X1R5G5B5;
		}
		break;
		case TFR5G6B5:
		{
			return D3DFMT_R5G6B5;
		}
		break;
		case TFD16:
		{
			return D3DFMT_D16;
		}
		break;
		case TFD32:
		{
			return D3DFMT_D32;//most card not support
		}
		break;
		case TFD24X8:
		{
			return D3DFMT_D24X8;
		}
		break;
		case TFA16B16G16R16F:
		{
			return D3DFMT_A16B16G16R16F;
		}
		break;;
		default:
		{
			return D3DFMT_UNKNOWN;
		}
		break;
	}
}

void D3D9RenderSystem::CreateDefaultRender(const RenderPath* pPath)
{
	D3D9Render* pRender = new D3D9Render(pPath);
	pRender->m_pDevice = m_pD3DDevice;
	m_pDefaultRender = pRender;
	InitRender(pRender);
}

HardwareVertexShader* D3D9RenderSystem::GetHardwareVertexShader( VertexShaderDesc& vertexShaderDesc)
{
	string strDesc = GenerateVertexShaderDescString(vertexShaderDesc);
	if (m_mapHardwareVertexShader.find(strDesc) != std::end(m_mapHardwareVertexShader))
	{
		return m_mapHardwareVertexShader[strDesc];
	}
	const char* pCode = GetVertexShaderCode(vertexShaderDesc);
	unsigned int nCodeLength = strlen(pCode);
	if (pCode == nullptr)
	{
		return nullptr;
	}
	D3D9VertexShader* pShader = new D3D9VertexShader;
	LPD3DXBUFFER pdxCode;
	LPD3DXBUFFER pError;
	//
	if (D3DXCompileShader(pCode, nCodeLength, NULL, NULL, "vMain", "vs_3_0", D3DXSHADER_DEBUG, &pdxCode, &pError, &pShader->m_pConstantTable) != D3D_OK)
	{
		std::cout << "compile vertex shader:"<<vertexShaderDesc.m_pVertexShader->GetRefPath().c_str()<<" failed" << std::endl;
		std::cout << (char*)pError->GetBufferPointer() << std::endl;
		pError->Release();
		delete pShader;
		return nullptr;
	}
	if (m_pD3DDevice->CreateVertexShader((DWORD*)pdxCode->GetBufferPointer(), &pShader->m_pVertexShader) != D3D_OK)
	{
		std::cout << "create vertex shader:" << vertexShaderDesc.m_pVertexShader->GetRefPath().c_str() << " failed" << std::endl;
		delete pShader;
		pdxCode->Release();
		return nullptr;
	}
	pdxCode->Release();
	//build arg
	D3DXCONSTANTTABLE_DESC tableDesc;
	pShader->m_pConstantTable->GetDesc(&tableDesc);
	for (int i = 0; i < tableDesc.Constants; ++i)
	{
		D3DXHANDLE handle = pShader->m_pConstantTable->GetConstant(nullptr, i);
		D3DXCONSTANT_DESC const_desc[256];
		UINT nCount;
		pShader->m_pConstantTable->GetConstantDesc(handle, const_desc, &nCount);
		for (int j = 0; j < nCount; ++j)
		{
			ShaderConstantInfo info;
			info.m_strName = const_desc[j].Name;
			switch (const_desc[j].RegisterSet)
			{
				case D3DXRS_SAMPLER:
				{
					info.m_eRegType = REGSAMPLE;
				}
				break;
				default:
				{
					info.m_eRegType = REGINVALID;
				}
				break;
			}
			info.m_nRegIndex = const_desc[j].RegisterIndex;
			pShader->m_mapConstants[const_desc[j].Name] = info;
		}

	}

	//
	m_mapHardwareVertexShader[strDesc] = pShader;
	pShader->m_pDevice = m_pD3DDevice;

	return pShader;
}

HardwareFragShader* D3D9RenderSystem::GetHardwareFragShader( FragShaderDesc& fragShaderDesc)
{
	string strDesc = GenerateFragShaderDescString(fragShaderDesc);
	if (m_mapHardwareFragShader.find(strDesc) != std::end(m_mapHardwareFragShader))
	{
		return m_mapHardwareFragShader[strDesc];
	}
	const char* pCode = GetFragShaderCode(fragShaderDesc);
	unsigned int nCodeLength = strlen(pCode);
	if (pCode == nullptr)
	{
		return nullptr;
	}
	D3D9FragShader* pShader = new D3D9FragShader;
	LPD3DXBUFFER pdxCode;
	LPD3DXBUFFER pError;
	//
	if (D3DXCompileShader(pCode, nCodeLength, NULL, NULL, "pMain", "ps_3_0", D3DXSHADER_DEBUG, &pdxCode, &pError, &pShader->m_pConstantTable) != D3D_OK)
	{
		std::cout << "compile pixel shader:" << fragShaderDesc.m_pFragShader->GetRefPath().c_str() << " failed" << std::endl;
		std::cout << (char*)pError->GetBufferPointer() << std::endl;
		pError->Release();
		delete pShader;
		return nullptr;
	}
	if (m_pD3DDevice->CreatePixelShader((DWORD*)pdxCode->GetBufferPointer(), &pShader->m_pFragShader) != D3D_OK)
	{
		std::cout << "create pixel shader:" << fragShaderDesc.m_pFragShader->GetRefPath().c_str() << " failed" << std::endl;
		delete pShader;
		pdxCode->Release();
		return nullptr;
	}
	pdxCode->Release();
	//build arg
	D3DXCONSTANTTABLE_DESC tableDesc;
	pShader->m_pConstantTable->GetDesc(&tableDesc);
	for (int i = 0; i < tableDesc.Constants; ++i)
	{
		D3DXHANDLE handle = pShader->m_pConstantTable->GetConstant(nullptr, i);
		D3DXCONSTANT_DESC const_desc[256];
		UINT nCount;
		pShader->m_pConstantTable->GetConstantDesc(handle, const_desc, &nCount);
		for (int j = 0; j < nCount; ++j)
		{
			ShaderConstantInfo info;
			info.m_strName = const_desc[j].Name;
			switch (const_desc[j].RegisterSet)
			{
				case D3DXRS_SAMPLER:
				{
					info.m_eRegType = REGSAMPLE;
				}
				break;
				default:
				{
					info.m_eRegType = REGINVALID;
				}
				break;
			}
			info.m_nRegIndex = const_desc[j].RegisterIndex;
			pShader->m_mapConstants[const_desc[j].Name] = info;
		}

	}
	m_mapHardwareFragShader[strDesc] = pShader;
	pShader->m_pDevice = m_pD3DDevice;
	return pShader;
}

HardwareVertexBuffer* D3D9RenderSystem::GetHardwareVertexBuffer(VertexData* pData)
{
	if (pData == nullptr)
	{
		return nullptr;
	}
	if (m_VertexDataMap.find(pData) != std::end(m_VertexDataMap))
	{
		return m_VertexDataMap[pData];
	}
	DynamicVertexData* pDynamicVertexData = dynamic_cast<DynamicVertexData*>(pData);
	if (pDynamicVertexData)
	{
		D3D9VertexBuffer* pBuff = new D3D9VertexBuffer();
		pBuff->m_eType = pDynamicVertexData->m_PrimitiveType;
		if (pDynamicVertexData->vecDataDesc.size() == 0)
		{
			pDynamicVertexData->autoGenDesc();
		}
		pBuff->m_pVertexBuffDecal = CreateVertexDeclarationFromDesc(pDynamicVertexData->vecDataDesc);
		pBuff->m_nNumVertex = pData->nNumVertex;
		pBuff->m_nStrip = pData->GetVertexDataLength();
		//
		if (FAILED(m_pD3DDevice->CreateVertexBuffer(pData->nNumVertex * pData->GetVertexDataLength(),
			0, 0,
			D3DPOOL_MANAGED, &pBuff->m_pVertexBuffer, NULL)))
		{
			delete pBuff;
			return nullptr;
		}
		void* pVertexData;
		if (FAILED(pBuff->m_pVertexBuffer->Lock(0, pData->GetVertexDataLength() * pData->nNumVertex, &pVertexData, 0)))
		{
			delete pBuff;
			return nullptr;
		}
		float* pFVertexData = (float*)pVertexData;
		for (int i = 0; i < pData->nNumVertex; ++i)
		{
			memcpy(pFVertexData + i * 3 + 0, &pDynamicVertexData->m_PositionData[i].m_fx, sizeof(float));
			memcpy(pFVertexData + i * 3 + 1, &pDynamicVertexData->m_PositionData[i].m_fy, sizeof(float));
			memcpy(pFVertexData + i * 3 + 2, &pDynamicVertexData->m_PositionData[i].m_fz, sizeof(float));
		}
		pBuff->m_pVertexBuffer->Unlock();
		m_VertexDataMap[pData] = pBuff;
		return pBuff;
	}
	
	MeshVertexData* pMeshVertexData = dynamic_cast<MeshVertexData*>(pData);
	if (pMeshVertexData != nullptr)
	{
		D3D9VertexBuffer* pBuff = new D3D9VertexBuffer();
		pBuff->m_pVertexBuffDecal = CreateVertexDeclarationFromDesc(pMeshVertexData->vecDataDesc);
		pBuff->m_nNumVertex = pData->nNumVertex;
		pBuff->m_nStrip = pMeshVertexData->GetVertexDataLength();
		//
		if (FAILED(m_pD3DDevice->CreateVertexBuffer(pMeshVertexData->nNumVertex * pMeshVertexData->GetVertexDataLength(),
			0, 0,
			D3DPOOL_MANAGED, &pBuff->m_pVertexBuffer, NULL)))
		{
			delete pBuff;
			return nullptr;
		}

		///
		void* pVertexData;
		if (FAILED(pBuff->m_pVertexBuffer->Lock(0, pMeshVertexData->GetVertexDataLength() * pMeshVertexData->nNumVertex, &pVertexData, 0)))
		{
			delete pBuff;
			return nullptr;
		}

		float* pf = (float*)pMeshVertexData->pData;
		//for (int i = 0; i < 4; ++i)
		//{
		//	 pf[3 + i * 11] = fabs(pf[8 + i * 11]);
		//	 pf[4 + i * 11] = fabs(pf[9 + i * 11]);
		//	   pf[5 + i * 11] = fabs(pf[10 + i * 11]);
		//}
		memcpy(pVertexData, pf, pMeshVertexData->GetVertexDataLength() * pMeshVertexData->nNumVertex);
		pBuff->m_pVertexBuffer->Unlock();
		m_VertexDataMap[pData] = pBuff;
		return pBuff;
	}
	return nullptr;

}
HardwareIndexBuffer* D3D9RenderSystem::GetHardwareIndexBuffer(IndexData* pData)
{
	if (pData == nullptr)
	{
		return nullptr;
	}
	if (m_IndexDataMap.find(pData) != std::end(m_IndexDataMap))
	{
		return m_IndexDataMap[pData];
	}
	//
	//
	unsigned int sizeIndex = 2;
	D3DFORMAT indexFormat = D3DFMT_INDEX16;
	if (pData->indexDesc == EIndexInt)
	{
		sizeIndex = 4;
		indexFormat = D3DFMT_INDEX32;
	}
	D3D9IndexBuffer* pBuff = new D3D9IndexBuffer();
	HRESULT hr;
	if (FAILED(hr = m_pD3DDevice->CreateIndexBuffer(pData->indexNum * sizeIndex, 0, indexFormat, D3DPOOL_MANAGED, &pBuff->m_pIndexBuffer, 0)))
	{
		delete pBuff;
		return nullptr;
	}
	
	pBuff->m_IndexDesc = pData->indexDesc;
	pBuff->m_nIndexNum = pData->indexNum;
	void* pIndexData;
	///
	hr = pBuff->m_pIndexBuffer->Lock(0, 0, &pIndexData, 0);
	if (SUCCEEDED(hr))
	{
		memcpy(pIndexData, pData->pData, pBuff->m_nIndexNum * sizeIndex);
	}
	pBuff->m_pIndexBuffer->Unlock();
	//
	m_IndexDataMap[pData] = pBuff;
	//
	return pBuff;
}

stD3DVertexBuffDecal* D3D9RenderSystem::CreateVertexDeclarationFromDesc(std::vector<VertexData::VertexDataDesc>& vecDataDesc)
{
	std::vector<D3DVERTEXELEMENT9> vecVertElem;
	int nOffset = 0;
	D3DVERTEXELEMENT9 elem;
	std::unordered_map<BYTE, unsigned char> useIndexMap;
	for each (VertexData::VertexDataDesc desc in vecDataDesc)
	{
		D3DDECLTYPE type = GetD3DDeclType(desc.typedesc);
		BYTE		usage = GetD3DDeclUsage(desc.usedesc);
		elem = { 0, nOffset, type, D3DDECLMETHOD_DEFAULT, usage, useIndexMap[usage] };
		useIndexMap[usage] = useIndexMap[usage] + 1;
		vecVertElem.push_back(elem);
		nOffset += MeshVertexData::GetTypeLength(desc);
	}
	vecVertElem.push_back(D3DDECL_END());

	stD3DVertexBuffDecal* pDecal = GetVertexDecal(vecDataDesc);
	if (pDecal != nullptr)
	{
		return pDecal;
	}
	pDecal = new stD3DVertexBuffDecal;
	IDirect3DVertexDeclaration9*	pVertexDecl = nullptr;
	m_pD3DDevice->CreateVertexDeclaration((D3DVERTEXELEMENT9*)(&vecVertElem[0]), &pVertexDecl);
	pDecal->m_pVertexDecal = pVertexDecl;
	pDecal->m_vecDataDesc = vecDataDesc;
	return pDecal;
}

D3DDECLTYPE D3D9RenderSystem::GetD3DDeclType(EnumVertexTypeDesc desc) const
{
	switch (desc)
	{
		case EVertexTypeInvalid:
		{
			return D3DDECLTYPE_UNUSED;
		}
		break;
		case EVertexTypeFloat1:
		{
			return D3DDECLTYPE_FLOAT1;
		}
		break;
		case EVertexTypeFloat2:
		{
			return D3DDECLTYPE_FLOAT2;
		}
		break;
		case EVertexTypeFloat3:
		{
			return D3DDECLTYPE_FLOAT3;
		}
		break;
		case EVertexTypeFloat4:
		{
			return D3DDECLTYPE_FLOAT4;
		}
		break;
		case EVertexTypeUByte4:
		{
			return D3DDECLTYPE_UBYTE4;
		}
		break;
		default:
		{
			return D3DDECLTYPE_UNUSED; 
		}		
		break;
	}
}

BYTE D3D9RenderSystem::GetD3DDeclUsage(EnumVertexUseDesc desc) const
{
	switch (desc)
	{
		case EVertexInvalid:
		{
			return -1;
		}
		break;
		case EVertexPosition:
		{
			return D3DDECLUSAGE_POSITION;
		}
		break;
		case EVertexNormal:
		{
			return D3DDECLUSAGE_NORMAL;
		}
		break;
		case EVertexTangent:
		{
			return D3DDECLUSAGE_TANGENT;
		}
		break;
		case EVertexColor:
		{
			return D3DDECLUSAGE_COLOR;
		}
		break;
		case EVertexUV:
		{
			return D3DDECLUSAGE_TEXCOORD;
		}
		break;
		case EVertexBlendIndex:
		{
			return D3DDECLUSAGE_BLENDINDICES;
		}
		break;
		case EVertexBlendWeight:
		{
			return D3DDECLUSAGE_BLENDWEIGHT;
		}
		break;
		default:
		{
			return -1;
		}
		break;
	}
}

HardwareTexture* D3D9RenderSystem::GetHardwareTexture(SmartPointer<Texture> pTexture)
{
	if (pTexture == nullptr)
	{
		return nullptr;
	}
	if (m_mapTexture.find(pTexture->GetRefPath()) != std::end(m_mapTexture))
	{
		return m_mapTexture[pTexture->GetRefPath()];
	}
	switch (pTexture->GetTexType())
	{
		case ETEXTYPE2D:
		{
			D3D9Texture2D* pHardwareTex = new D3D9Texture2D;
			if (D3DXCreateTextureFromFile(m_pD3DDevice, pTexture->GetRefPath().c_str(), &pHardwareTex->m_pTexture))
			//if (FAILED(D3DXCreateTextureFromFileEx
			//	(
			//	m_pD3DDevice,
			//	pTexture->GetRefPath().c_str(), 
			//	D3DX_DEFAULT,
			//	D3DX_DEFAULT,
			//	D3DX_DEFAULT,
			//	0,
			//	D3DFMT_FROM_FILE,
			//	D3DPOOL_MANAGED,
			//	D3DX_DEFAULT,
			//	D3DX_DEFAULT,
			//	0,
			//	nullptr,
			//	nullptr,
			//	&pHardwareTex->m_pTexture
			//	)))
			{
				//std::cout << "can not find texture:" << pTexture->GetRefPath().c_str() << std::endl;
				delete pHardwareTex;	
				//MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
				return nullptr;
			}
			m_mapTexture[pTexture->GetRefPath()] = pHardwareTex;
			return pHardwareTex;
		}
		break;
		case ETEXTYPECUBE:
		{

		}
		break;
		default:
		{
			return nullptr;
		}
		break;
	}
	
	return nullptr;
}

IRenderTarget* D3D9RenderSystem::CreateRenderTarget(unsigned int nWidth, unsigned int nHeight, TARGETFORMAT eTarget, EMULTISAMPLETYPE eMultiSample, unsigned int nQuality,int nDepth)
{
	D3D9RenderTarget* pTarget = new D3D9RenderTarget;
	D3DFORMAT d3dFormat = getBufferFormat(eTarget);
	IDirect3DTexture9* pTexture;
	if (D3D_OK != m_pD3DDevice->CreateTexture(nWidth, nHeight, 1, D3DUSAGE_RENDERTARGET, d3dFormat, D3DPOOL_DEFAULT, &pTexture, nullptr))
	{
		std::cout << "create rendertarget texture failed!" << std::endl;
	}
	//
	pTarget->m_nWidth = nWidth;
	pTarget->m_nHeight = nHeight;
	pTarget->m_eTargetFormt = eTarget;
	//
	//pTexture->GetSurfaceLevel(0, &pTarget->m_pSurface);
	pTarget->m_pSurfTexture = pTexture;
	pTarget->m_pD3DDevice = m_pD3DDevice;
	m_vecRenderTarget.push_back(pTarget);
	if (nDepth != 0)
	{
		pTarget->m_DepthBuffer = CreateDepthBuffer(pTarget->m_nWidth, pTarget->m_nHeight, nDepth);
	}
	return pTarget;
}

bool D3D9RenderSystem::OnFrameBegin()
{
	if (m_pD3DDevice == nullptr)
	{
		return false;
	}
	HRESULT hr = m_pD3DDevice->TestCooperativeLevel();
	switch (hr)
	{
		case D3DERR_DEVICELOST:
		{
			//for each (std::pair< std::vector<D3DVERTEXELEMENT9>, IDirect3DVertexDeclaration9*>& p in m_DecalMap)
			//{
			//	if (p.second != nullptr)
			//	{
			//		p.second->Release();
			//		p.second = nullptr;
			//	}
			//}

			return false;
		}
		break;
		case D3DERR_DEVICENOTRESET:
		{
			{
				std::vector<stD3DVertexBuffDecal*>::iterator iter = m_VertexDecals.begin();
				for (; iter != m_VertexDecals.end(); ++iter)
				{
					SAFE_RELEASE((*iter)->m_pVertexDecal);
				}

				std::vector<SmartPointer<IRenderTarget>>::iterator iterRT = m_vecRenderTarget.begin();
				for (; iterRT != m_vecRenderTarget.end(); ++iterRT)
				{
					IRenderTarget* pTarget = (*iterRT).get();
					D3D9RenderTarget* pD3DTarget = dynamic_cast<D3D9RenderTarget*>(pTarget);
					D3D9RenderView* pD3DView = dynamic_cast<D3D9RenderView*>(pTarget);
					if (pD3DTarget != nullptr)
					{
						pD3DTarget->OnDeviceLost();
					}
					if (pD3DView != nullptr)
					{
						pD3DView->OnDeviceLost();
					}
				}
				std::vector<SmartPointer<DepthBuffer>>::iterator iterDpth = m_vecDepthBuffer.begin();
				for (; iterDpth != m_vecDepthBuffer.end(); ++iterDpth)
				{
					D3DDepthBuffer* pDepthBuffer = dynamic_cast<D3DDepthBuffer*>((*iterDpth).get());
					if (pDepthBuffer != nullptr)
					{
						pDepthBuffer->OnDeviceLost();
					}
				}
			}
			//////////////////////////////////reset
			HRESULT hr = m_pD3DDevice->Reset(&m_D3DPresentParamenter);
			if (EnviromentSetting::GetInstance()->GetIntSetting("LinearLighting") == true)
			{
				m_pD3DDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, TRUE);
			}

			if (hr != D3D_OK)
			{
				
				std::cout << "reset device failed!" << std::endl;
				return false;
			}
			std::vector<stD3DVertexBuffDecal*>::iterator iter = m_VertexDecals.begin();
			for (; iter != m_VertexDecals.end(); ++iter)
			{
				std::vector<VertexData::VertexDataDesc> vecDataDesc = (*iter)->m_vecDataDesc;
				std::vector<D3DVERTEXELEMENT9> vecVertElem;
				int nOffset = 0;
				D3DVERTEXELEMENT9 elem;
				std::unordered_map<BYTE, unsigned char> useIndexMap;
				for each (VertexData::VertexDataDesc desc in vecDataDesc)
				{
					D3DDECLTYPE type = GetD3DDeclType(desc.typedesc);
					BYTE		usage = GetD3DDeclUsage(desc.usedesc);
					elem = { 0, nOffset, type, D3DDECLMETHOD_DEFAULT, usage, useIndexMap[usage] };
					useIndexMap[usage] = useIndexMap[usage] + 1;
					vecVertElem.push_back(elem);
					nOffset += MeshVertexData::GetTypeLength(desc);
				}
				vecVertElem.push_back(D3DDECL_END());
				m_pD3DDevice->CreateVertexDeclaration(&vecVertElem[0], &(*iter)->m_pVertexDecal);
			}

			std::vector<SmartPointer<IRenderTarget>>::iterator iterRT = m_vecRenderTarget.begin();
			for (; iterRT != m_vecRenderTarget.end(); ++iterRT)
			{
				IRenderTarget* pTarget = (*iterRT).get();
				D3D9RenderTarget* pD3DTarget = dynamic_cast<D3D9RenderTarget*>(pTarget);
				D3D9RenderView* pD3DView = dynamic_cast<D3D9RenderView*>(pTarget);
				if (pD3DTarget != nullptr)
				{
					pD3DTarget->OnDeviceReset();
				}
				if (pD3DView != nullptr)
				{
					pD3DView->OnDeviceReset();
				}
			}
			std::vector<SmartPointer<DepthBuffer>>::iterator iterDpth = m_vecDepthBuffer.begin();
			for (; iterDpth != m_vecDepthBuffer.end(); ++iterDpth)
			{
				D3DDepthBuffer* pDepthBuffer = dynamic_cast<D3DDepthBuffer*>((*iterDpth).get());
				if (pDepthBuffer != nullptr)
				{
					pDepthBuffer->OnDeviceReset();
				}
			}

			return false;
		}
		break;
	}
	return true;
}

void D3D9RenderSystem::OnFrameEnd()
{
	//for each (SmartPointer<IRenderTarget> pView in m_vecRenderTarget)
	//{
	//	D3D9RenderView* pTargetView = dynamic_cast<D3D9RenderView*>(pView.get());
	//	if (pTargetView != nullptr && pTargetView->m_pSwapChain != nullptr && pTargetView->m_nIndex != 0)
	//	{
	//		D3DPRESENT_PARAMETERS dpp;
	//		pTargetView->m_pSwapChain->GetPresentParameters(&dpp);
	//		if (dpp.BackBufferHeight != pTargetView->m_dpp.BackBufferHeight || dpp.BackBufferWidth != pTargetView->m_dpp.BackBufferWidth)
	//		{
	//			pTargetView->Resize(pTargetView->m_dpp.BackBufferWidth, pTargetView->m_dpp.BackBufferHeight);
	//		}
	//	}
	//}
}

stD3DVertexBuffDecal* D3D9RenderSystem::GetVertexDecal(std::vector<VertexData::VertexDataDesc>& decl)
{
	for each (stD3DVertexBuffDecal* pDecal in m_VertexDecals)
	{
		if (pDecal->m_vecDataDesc.size() != decl.size())
		{
			continue;
		}
		for (int i = 0; i < decl.size();++i)
		{
			if (pDecal->m_vecDataDesc[i].nOffset == decl[i].nOffset
				&&pDecal->m_vecDataDesc[i].typedesc == decl[i].typedesc
				&&pDecal->m_vecDataDesc[i].usedesc == decl[i].usedesc)
			{
				return pDecal;
			}
		}
	}
	return nullptr;
}

RenderView* D3D9RenderSystem::CreateRenderView(stRenderViewInfo& viewInfo,int nDepth)
{
	D3D9RenderView* pView = new D3D9RenderView;
	//D3DPRESENT_PARAMETERS dpp;
	//
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferHeight = viewInfo.m_nHeight;
	d3dpp.BackBufferWidth = viewInfo.m_nWidth;
	d3dpp.BackBufferCount = 1;
	d3dpp.Windowed = viewInfo.m_bWindowed;
	d3dpp.SwapEffect = getSwapEffect(viewInfo.m_eSwapEffect);
	d3dpp.BackBufferFormat = getBufferFormat(viewInfo.m_eTargetFormt);
	d3dpp.EnableAutoDepthStencil =  viewInfo.m_bDepth;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.hDeviceWindow = (HWND)viewInfo.m_windowID;
	if (viewInfo.m_bDepth == true)
	{
		d3dpp.AutoDepthStencilFormat = getBufferFormat(viewInfo.m_eDepthFormt);
	}
	pView->m_dpp = d3dpp;
	//m_D3DPresentParamenter = d3dpp;
	//
	HRESULT hr = m_pD3DDevice->CreateAdditionalSwapChain(&d3dpp, &pView->m_pSwapChain);
	pView->m_pD3DDevice = m_pD3DDevice;
	pView->m_nIndex = -1;
	pView->m_nWidth = viewInfo.m_nWidth;
	pView->m_nHeight = viewInfo.m_nHeight;
	if (hr != D3D_OK)
	{
		std::cout << "create view failed!" << std::endl;
		delete pView;
		return nullptr;

	}
	else
	{
		//std::cout << "create view success!" << std::endl;
	}
	if (nDepth != 0)
	{
		pView->m_DepthBuffer = CreateDepthBuffer(pView->m_nWidth, pView->m_nHeight, nDepth);
	}
	if (EnviromentSetting::GetInstance()->GetIntSetting("HDR") == true)
	{
		pView->CreateHdrTarget();
	}
	m_vecRenderTarget.push_back(pView);
	return pView;
}

DepthBuffer* ZG::D3D9RenderSystem::CreateDepthBuffer(int nWidth, int nHeight, int nDepth)
{
	if (nDepth <= 0)
	{
		return nullptr;
	}
	D3DDepthBuffer* pBuffer = new D3DDepthBuffer;
	D3DFORMAT d3dFormat;
	switch (nDepth)
	{
		case 16:
		{
			d3dFormat = D3DFMT_D16;
		}
		break;
		case 24:
		{
			d3dFormat = D3DFMT_D24S8;
		}
		break;
		default:
		break;
	}
	pBuffer->m_nDepth = nDepth;
	pBuffer->m_nWidth = nWidth;
	pBuffer->m_nHeight = nHeight;
	pBuffer->m_pD3DDevice = m_pD3DDevice;
	m_pD3DDevice->CreateDepthStencilSurface(nWidth, nHeight, d3dFormat, D3DMULTISAMPLE_NONE, 0, true, &pBuffer->m_pDepthSurface, nullptr);
	if (pBuffer->m_pDepthSurface == nullptr)
	{
		std::cout << "create DepthBuffer Failed!" << std::endl;
		delete pBuffer;
		return nullptr;
	}
	m_vecDepthBuffer.push_back(pBuffer);
	return pBuffer;
}
