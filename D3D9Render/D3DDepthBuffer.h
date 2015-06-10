#pragma once
#include "DepthBuffer.h"
struct IDirect3DSurface9;
struct IDirect3DDevice9;
namespace ZG
{
	class D3DDepthBuffer:public DepthBuffer
	{
	public:
		D3DDepthBuffer();
		virtual ~D3DDepthBuffer();
		void OnDeviceLost();
		void OnDeviceReset();
		bool Resize(int nWidth, int nHeight) override;
		IDirect3DSurface9* m_pDepthSurface;


		IDirect3DDevice9*	m_pD3DDevice;

	};

}

