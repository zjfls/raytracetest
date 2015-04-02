#include "stdafx.h"
#include "D3D9Application.h"
#include "IWorld.h"
#include "IWorldObj.h"
#include "EnviromentSetting.h"
#include "AssetManager.h"
#include "PrefabResource.h"
#include "ResourceManager.h"
#include "PrefabResource.h"
#include "RasterCamera.h"
#include "CameraRenderer.h"
#include "RenderManager.h"
#include "RenderSystem.h"
#include "MathFunc.h"
#include "RenderView.h"
template class MAIN_API  Singleton < D3D9Application>;
template<> shared_ptr<D3D9Application> Singleton<D3D9Application>::_instance = nullptr;

D3D9Application::D3D9Application()
{
}


D3D9Application::~D3D9Application()
{
}

void D3D9Application::OnInit()
{
	AssetManager::GetInstance()->LoadAsset("./data/shader/VertexStandard.vsm");
}

void D3D9Application::SetupScene()
{
	AssetManager::GetInstance()->LoadAsset("./data/meshes/porlfull.prefab.xml");
	shared_ptr<PrefabResource> pPrefab = ResourceManager<PrefabResource>::GetInstance()->GetResource("./data/meshes/porlfull.prefab.xml");
	IWorldObj* pObj = pPrefab->m_pRoot->Clone(true);
	m_pWorld->m_pRoot->addChild(pObj);



	IWorldObj* pCamera = new IWorldObj;
	m_pWorld->m_pRoot->addChild(pCamera);
	RasterCamera* pCameraModule = pCamera->addModule<RasterCamera>();


	CameraRenderer* pCameraRenderer = new CameraRenderer;
	pCameraRenderer->m_pWorld = m_pWorld;
	pCameraRenderer->m_pTarget = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRenderView();
	pCameraRenderer->m_pRender = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRender();
	pCameraModule->AddListener("CameraRenderer", pCameraRenderer);

	pCamera->m_pTransform->SetTranslate(Vector3(0.0f,100.0f,-650.0f));
	pCamera->m_pTransform->SetOrientation(AngleToRad(-80.0f), 0, 0);


}

void D3D9Application::OnEndInit()
{

}

void D3D9Application::Run()
{
	ShowWindow((HWND)m_RenderViewInfo.m_windowID, SW_SHOWDEFAULT);
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
				m_pRenderView->Present();
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
		m_RenderViewInfo.m_nWidth, m_RenderViewInfo.m_nHeight, 0, 0, GetModuleHandle(0), 0);
	m_RenderViewInfo.m_windowID = (int)window;
	//ShowWindow(window, SW_SHOWDEFAULT);
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
