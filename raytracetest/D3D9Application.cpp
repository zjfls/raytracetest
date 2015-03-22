#include "stdafx.h"
#include "D3D9Application.h"
#include "IWorld.h"
D3D9Application* Singleton<D3D9Application>::_instance = nullptr;

D3D9Application::D3D9Application()
{
}


D3D9Application::~D3D9Application()
{
}

void D3D9Application::OnInit()
{

}

void D3D9Application::SetupScene()
{

}

void D3D9Application::OnEndInit()
{

}

void D3D9Application::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (m_pWorld != nullptr)
			{
				m_pWorld->Update();
			}
		}
	}
}

void D3D9Application::CleanUp()
{

}

bool D3D9Application::CreateAppWindow()
{
	const char* const myclass = "myclass";
	WNDCLASSEX wndclass = { sizeof(WNDCLASSEX), CS_DBLCLKS, WindowProcedure,
		0, 0, GetModuleHandle(0), LoadIcon(0, IDI_APPLICATION),
		LoadCursor(0, IDC_ARROW), HBRUSH(COLOR_WINDOW + 1),
		0, myclass, LoadIcon(0, IDI_APPLICATION) };
	RegisterClassEx(&wndclass);
	HWND window = CreateWindowEx(0, myclass, "d3dwindow",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		1024, 768, 0, 0, GetModuleHandle(0), 0);
	m_RenderViewInfo.m_windowID = (unsigned int)window;
	m_RenderViewInfo.m_nHeight = 768;
	m_RenderViewInfo.m_nWidth = 1024;
	ShowWindow(window, SW_SHOWDEFAULT);
	return true;
}

long __stdcall D3D9Application::WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_DESTROY:
		std::cout << "\ndestroying window\n";
		D3D9Application::GetInstance()->CleanUp();
		PostQuitMessage(0);
		return 0L;
		case WM_LBUTTONDOWN:
		//std::cout << "\nmouse left button down at (" << LOWORD(lp)
		//	<< ',' << HIWORD(lp) << ")\n";
		// fall thru
		default:
		//std::cout << '.';
		return DefWindowProc(window, msg, wp, lp);
	}
}
