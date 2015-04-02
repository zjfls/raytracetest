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

D3D9RenderSystem::D3D9RenderSystem()
	:m_pD3D(nullptr)
	, m_pD3DDevice(nullptr)
{
}


D3D9RenderSystem::~D3D9RenderSystem()
{
}
bool test(const stRenderViewInfo& viewInfo)
{
	LPDIRECT3D9 pd3d;
	LPDIRECT3DDEVICE9 pd3ddevice9;
	if (FAILED(pd3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		std::cout << "get d3d9 object failed!" << std::endl;
		return false;
	}

	//D3DDISPLAYMODE displaymode;
	//ZeroMemory(&displaymode, sizeof(displaymode));
	//LPDIRECT3D9EX pd3d = D3D9Manager::GetInstance()->m_pD3D;
	//int nModeCount = pd3d->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8);
	////pd3d->EnumAdapterModes(D3DADAPTER_DEFAULT,)
	//for (int i = 0; i < nModeCount; ++i)
	//{
	//	D3DDISPLAYMODE mode;
	//	pd3d->EnumAdapterModes(D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8, i, &mode);

	//	std::cout << "displaymode D3DFMT_X8R8G8B8:" << mode.Width << " " << mode.Height << " " << mode.RefreshRate << std::endl;
	//}
	//nModeCount = pd3d->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_A8R8G8B8);
	//for (int i = 0; i < nModeCount; ++i)
	//{
	//	D3DDISPLAYMODE mode;
	//	pd3d->EnumAdapterModes(D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8, i, &mode);

	//	std::cout << "displaymode D3DFMT_A8R8G8B8:" << mode.Width << " " << mode.Height << " " << mode.RefreshRate << std::endl;
	//}
	//HRESULT hr1 = pd3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displaymode);
	//if (FAILED(pd3d->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, displaymode.Format, D3DUSAGE_RENDERTARGET, D3DRTYPE_SURFACE, D3DFMT_A8R8G8B8)))
	//{
	//	MessageBox(NULL, "Device format is unaccepatble for full screen mode", "Sorry", MB_OK);
	//	return false;
	//}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = false;    // program fullscreen, not windowed
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
	d3dpp.hDeviceWindow = (HWND)viewInfo.m_windowID;    // set the window to be used by Direct3D
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;    // set the back buffer format to 32-bit
	d3dpp.BackBufferWidth = 1024;    // set the width of the buffer
	d3dpp.BackBufferHeight = 768;    // set the height of the buffer
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;
	//d3dpp.Flags = D3DPRESENTFLAG_UNPRUNEDMODE;
	d3dpp.PresentationInterval = 0;
	//d3dpp.FullScreen_RefreshRateInHz = 60;


	HRESULT hr;
	if (FAILED(hr = pd3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, HWND(viewInfo.m_windowID),
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &pd3ddevice9)))
	{
		std::cout << "create device failed" << std::endl;
		std::cout << hr << std::endl;
		//system("pause");
		return false;
	}
	return true;
	//
}
bool D3D9RenderSystem::InitRenderSystem(const stRenderViewInfo& viewInfo)
{
	//return test(viewInfo);
	//return;
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &m_pD3D)))
	{
		std::cout << "get d3d9 object failed!" << std::endl;
		return false;
	}
	//
	D3DDISPLAYMODE displaymode;
	ZeroMemory(&displaymode,sizeof(displaymode));
	LPDIRECT3D9EX pd3d = m_pD3D;
	int nModeCount = pd3d->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8);
	//pd3d->EnumAdapterModes(D3DADAPTER_DEFAULT,)
	for (int i = 0; i < nModeCount; ++i)
	{
		D3DDISPLAYMODE mode;
		pd3d->EnumAdapterModes(D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8, i, &mode);

		std::cout << "displaymode D3DFMT_X8R8G8B8:" << mode.Width << " " << mode.Height << " " << mode.RefreshRate << std::endl;
	}
	nModeCount = pd3d->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_A8R8G8B8);
	for (int i = 0; i < nModeCount; ++i)
	{
		D3DDISPLAYMODE mode;
		pd3d->EnumAdapterModes(D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8, i, &mode);

		std::cout << "displaymode D3DFMT_A8R8G8B8:" << mode.Width << " " << mode.Height << " " << mode.RefreshRate << std::endl;
	}
	HRESULT hr1 = m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displaymode);
	if (FAILED(m_pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, displaymode.Format, D3DUSAGE_RENDERTARGET, D3DRTYPE_SURFACE, D3DFMT_A8R8G8B8)))
	{
		//MessageBox(NULL, "Device format is unaccepatble for full screen mode", "Sorry", MB_OK);
		return false;
	}
	//
	//create device


	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	//d3dpp.Windowed = true;    // program fullscreen, not windowed
	//d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
	//d3dpp.hDeviceWindow = (HWND)viewInfo.m_windowID;    // set the window to be used by Direct3D
	//d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;    // set the back buffer format to 32-bit
	//d3dpp.BackBufferWidth = 800;    // set the width of the buffer
	//d3dpp.BackBufferHeight = 600;    // set the height of the buffer
	//d3dpp.EnableAutoDepthStencil = true;
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;
	////d3dpp.Flags = D3DPRESENTFLAG_UNPRUNEDMODE;
	//d3dpp.PresentationInterval = 0;
	//d3dpp.BackBufferCount = 2;
	d3dpp.BackBufferHeight = viewInfo.m_nHeight;
	d3dpp.BackBufferWidth = viewInfo.m_nWidth;
	d3dpp.BackBufferCount = 2;
	d3dpp.Windowed = viewInfo.m_bWindowed;
	d3dpp.SwapEffect = getSwapEffect(viewInfo.m_eSwapEffect);
	d3dpp.BackBufferFormat = getBufferFormat(viewInfo.m_eTargetFormt);
	d3dpp.EnableAutoDepthStencil = viewInfo.m_bDepth;
	//d3dpp.Flags = D3DPRESENTFLAG_VIDEO;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	d3dpp.hDeviceWindow = (HWND)viewInfo.m_windowID;
	if (viewInfo.m_bDepth == true)
	{
		d3dpp.AutoDepthStencilFormat =  getBufferFormat(viewInfo.m_eDepthFormt);
	}
	D3DDISPLAYMODEEX d3dsm;
	ZeroMemory(&d3dsm, sizeof(d3dsm));
	d3dsm.Format = d3dpp.BackBufferFormat;
	d3dsm.Size = sizeof(D3DDISPLAYMODEEX);
	d3dsm.Width = d3dpp.BackBufferWidth;
	d3dsm.Height = d3dpp.BackBufferHeight;
	//d3dsm.RefreshRate = 60;
	//d3dsm.ScanLineOrdering = D3DSCANLINEORDERING_PROGRESSIVE;
	D3DDISPLAYMODEEX* pd3dsm = nullptr;
	if (d3dpp.Windowed == FALSE)
	{ 
		pd3dsm = &d3dsm;
	}


	HRESULT hr = 0;
	if (FAILED(hr = m_pD3D->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, HWND(viewInfo.m_windowID),
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, pd3dsm, &m_pD3DDevice)))
	{
		std::cout << "create device failed" << std::endl;
		std::cout << hr << std::endl;
		//system("pause");
		return false;
	}



	D3D9RenderView* pRenderView;
	IDirect3DSwapChain9* pSwapChain;
	m_pD3DDevice->GetSwapChain(0, &pSwapChain);
	pRenderView = new D3D9RenderView;
	pRenderView->m_pSwapChain = (IDirect3DSwapChain9Ex*)pSwapChain;
	m_pDefaultRenderView = pRenderView;



	//D3D9Manager::GetInstance()->m_pDefaultRender = new D3D9Render(RenderPathManager::GetInstance()->GetRenderPath(
	//	EnviromentSetting::GetInstance()->GetSetting("DefaultPath")));
	return true;
}

D3DSWAPEFFECT D3D9RenderSystem::getSwapEffect(const EBUFFSWARP eSwap) const
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

D3DFORMAT D3D9RenderSystem::getBufferFormat(const TARGETFORMAT eFormat) const
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

HardwareVertexShader* D3D9RenderSystem::GetHardwareVertexShader(const VertexShaderDesc& vertexShaderDesc)
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

	//
	m_mapHardwareVertexShader[strDesc] = pShader;

	return pShader;
}

HardwareFragShader* D3D9RenderSystem::GetHardwareFragShader(const FragShaderDesc& fragShaderDesc)
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
	m_mapHardwareFragShader[strDesc] = pShader;

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
	D3D9VertexBuffer* pBuff = new D3D9VertexBuffer();
	pBuff->m_pVertexDecal = CreateVertexDeclarationFromDesc(pData->vecDataDesc);
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

	///
	void* pVertexData;
	if (FAILED(pBuff->m_pVertexBuffer->Lock(0, pData->GetVertexDataLength() * pData->nNumVertex, &pVertexData, 0)))
	{
		delete pBuff;
		return nullptr;
	}

	float* pf = (float*)pData->pData;
	memcpy(pVertexData,pf,pData->GetVertexDataLength() * pData->nNumVertex);
	pBuff->m_pVertexBuffer->Unlock();

	return pBuff;
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
	if (FAILED(m_pD3DDevice->CreateIndexBuffer(pData->indexNum * sizeIndex, 0, indexFormat, D3DPOOL_MANAGED, &pBuff->m_pIndexBuffer, 0)))
	{
		delete pBuff;
		return nullptr;
	}
	
	pBuff->m_IndexDesc = pData->indexDesc;
	pBuff->m_nIndexNum = pData->indexNum;
	void* pIndexData;
	///
	HRESULT hr = pBuff->m_pIndexBuffer->Lock(0, 0, &pIndexData, 0);
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

IDirect3DVertexDeclaration9* D3D9RenderSystem::CreateVertexDeclarationFromDesc(std::vector<VertexData::VertexDataDesc>& vecDataDesc)
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
		nOffset += VertexData::GetTypeLength(desc);
	}
	vecVertElem.push_back(D3DDECL_END());
	IDirect3DVertexDeclaration9*	pVertexDecl = nullptr;
	m_pD3DDevice->CreateVertexDeclaration((D3DVERTEXELEMENT9*)(&vecVertElem[0]), &pVertexDecl);
	return pVertexDecl;
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

HardwareTexture* D3D9RenderSystem::GetHardwareTexture(shared_ptr<Texture> pTexture)
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
			if (FAILED(D3DXCreateTextureFromFile(m_pD3DDevice, pTexture->GetRefPath().c_str(), &pHardwareTex->m_pTexture)))
			{
				//MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
				return nullptr;
			}
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
