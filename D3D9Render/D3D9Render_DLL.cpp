// D3D9Render.cpp : 定义 DLL 应用程序的导出函数。
//
#include "stdafx.h"
//#include "stdafx.h"
//#include "D3D9Render_DLL.h"
#include "D3D9RenderSystem.h"
//
//// 这是导出变量的一个示例
//D3D9RENDER_API int nD3D9Render=0;
//
//// 这是导出函数的一个示例。
//D3D9RENDER_API int fnD3D9Render(void)
//{
//	return 42;
//}
class RenderSystem;
extern "C" D3D9RENDER_API RenderSystem* CreateRenderSystem()
{
	return new D3D9RenderSystem();
}

//// 这是已导出类的构造函数。
//// 有关类定义的信息，请参阅 D3D9Render.h
//CD3D9Render::CD3D9Render()
//{
//	return;
//}
