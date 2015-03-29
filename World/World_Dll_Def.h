#pragma once
#ifdef WORLD_DLL_EXPORTS
#define WORLD_API __declspec(dllexport)
#else
#define WORLD_API __declspec(dllimport)
#endif