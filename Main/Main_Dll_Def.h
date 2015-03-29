#pragma once
#ifdef MAIN_DLL_EXPORTS
#define MAIN_API __declspec(dllexport)
#else
#define MAIN_API __declspec(dllimport)
#endif