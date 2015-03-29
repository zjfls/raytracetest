#pragma once
#ifdef FOUNDATION_DLL_EXPORTS
#define FOUNDATION_API __declspec(dllexport)
#else
#define FOUNDATION_API __declspec(dllimport)
#endif