#pragma once
#ifdef RESOURCE_DLL_EXPORTS
#define RESOURCE_API __declspec(dllexport)
#else
#define RESOURCE_API __declspec(dllimport)
#endif

#ifdef RESOURCE_DLL_EXPORTS
#define RESOURCE_TEMPLATE
#else
#define RESOURCE_TEMPLATE extern
#endif
