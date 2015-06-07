#include "stdafx.h"
#include "WindowsIO.h"
#include "windows.h"

WindowsIO::WindowsIO()
{
}


WindowsIO::~WindowsIO()
{
}

bool WindowsIO::IsLBDown()
{
	return GetAsyncKeyState(VK_LBUTTON) < 0;
}

bool WindowsIO::IsKeyDown(char c)
{
	return GetAsyncKeyState(c) < 0;
}

bool WindowsIO::IsRBDown()
{
	return GetAsyncKeyState(VK_RBUTTON) < 0;
}
