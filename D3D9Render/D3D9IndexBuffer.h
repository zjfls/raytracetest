#pragma once
#include "HardwareIndexBuffer.h"
struct IDirect3DIndexBuffer9;
namespace ZG
{
	class D3D9IndexBuffer :
		public HardwareIndexBuffer
	{
	public:

		virtual ~D3D9IndexBuffer();


		IDirect3DIndexBuffer9* m_pIndexBuffer;
	private:
		D3D9IndexBuffer();
		friend class D3D9RenderSystem;
	};
}


