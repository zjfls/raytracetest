#include "stdafx.h"
#include "D3D9RenderSystem.h"
#include "D3D9Render.h"
#include "d3d9.h"
#include "D3D9Manager.h"
//#include "RenderView.h"
#include "D3D9RenderView.h"
#include "EnviromentSetting.h"
#include "RenderPathManager.h"

D3D9RenderSystem::D3D9RenderSystem()
{
}


D3D9RenderSystem::~D3D9RenderSystem()
{
}

bool D3D9RenderSystem::InitRenderSystem(const stRenderViewInfo& viewInfo) const
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &D3D9Manager::GetInstance()->m_pD3D)))
	{
		std::cout << "get d3d9 object failed!" << std::endl;
		return false;
	}
	//create device
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferHeight = viewInfo.m_nHeight;
	d3dpp.BackBufferWidth = viewInfo.m_nWidth;
	d3dpp.Windowed = viewInfo.m_bWindowed;
	d3dpp.SwapEffect = getSwapEffect(viewInfo.m_eSwapEffect);
	d3dpp.BackBufferFormat = getBufferFormat(viewInfo.m_eTargetFormt);
	d3dpp.EnableAutoDepthStencil = viewInfo.m_bDepth;
	//d3dpp.Flags = D3DPRESENTFLAG_VIDEO;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	if (viewInfo.m_bDepth == true)
	{
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;// getBufferFormat(viewInfo.m_eDepthFormt);
	}
	D3DDISPLAYMODEEX d3dsm;
	ZeroMemory(&d3dsm, sizeof(d3dsm));
	d3dsm.Format = getBufferFormat(viewInfo.m_eTargetFormt);
	d3dsm.Size = sizeof(D3DDISPLAYMODEEX);
	d3dsm.Width = viewInfo.m_nWidth;
	d3dsm.Height = viewInfo.m_nHeight;
	d3dsm.RefreshRate = viewInfo.m_nRefreshHZ;
	d3dsm.ScanLineOrdering = D3DSCANLINEORDERING_PROGRESSIVE;


	if (FAILED(D3D9Manager::GetInstance()->m_pD3D->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, HWND(viewInfo.m_windowID),
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,NULL, &D3D9Manager::GetInstance()->m_pD3DDevice)))
	{
		std::cout << "create device failed" << std::endl;
		std::cout << GetLastError() << std::endl;
		//system("pause");
		return false;
	}

	IDirect3DSwapChain9* pSwapChain;
	D3D9Manager::GetInstance()->m_pD3DDevice->GetSwapChain(0, &pSwapChain);
	D3D9Manager::GetInstance()->m_pDefaultRenderView = new D3D9RenderView;
	D3D9Manager::GetInstance()->m_pDefaultRenderView->m_pSwapChain = (IDirect3DSwapChain9Ex*)pSwapChain;



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
			return D3DFMT_A8B8G8R8;
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
			return D3DFMT_D32;
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

IRender* D3D9RenderSystem::GetDefaultRender() const
{
	return D3D9Manager::GetInstance()->m_pDefaultRender;
}

RenderView* D3D9RenderSystem::GetDefaultRenderView() const
{
	return D3D9Manager::GetInstance()->m_pDefaultRenderView;
}

void D3D9RenderSystem::CreateDefaultRender(const RenderPath* pPath) const
{
	D3D9Manager::GetInstance()->m_pDefaultRender = new D3D9Render(pPath);
}
