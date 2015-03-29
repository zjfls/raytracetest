#pragma once
#ifdef D3D9RENDER_DLL_EXPORTS
#define D3D9RENDER_API __declspec(dllexport)
#else
#define D3D9RENDER_API __declspec(dllimport)
#endif