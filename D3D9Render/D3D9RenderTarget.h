#pragma once
#include "IRenderTarget.h"
struct IDirect3DSurface9;
struct IDirect3DTexture9;
struct IDirect3DDevice9;
namespace ZG
{
	class D3D9RenderTarget :
		public IRenderTarget
	{
	public:
		D3D9RenderTarget();
		virtual ~D3D9RenderTarget();
		virtual	void OnDeviceLost();
		virtual void OnDeviceReset();
		bool Resize(int nWidth, int nHeight) override;


		IDirect3DTexture9* m_pSurfTexture;
		IDirect3DDevice9*	m_pD3DDevice;
		//IDirect3DSurface9* m_pSurface;
	};

}

