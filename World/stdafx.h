// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once
#define WORLD_DLL_EXPORTS
#include "targetver.h"
#include "World_Dll_Def.h"
#include "Math_Dll_Def.h"
#include "Resource_Dll_Def.h"
#include "Foundation_Dll_Def.h"
#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件: 
#include <windows.h>

#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <memory>
#include <math.h>
#include <assert.h>
#include <algorithm>
using namespace std;

#include "IRenderable.h"

// TODO:  在此处引用程序需要的其他头文件
