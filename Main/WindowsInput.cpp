#include "stdafx.h"
#include "WindowsInput.h"
#include "windows.h"

WindowsInput::WindowsInput()
{
}


WindowsInput::~WindowsInput()
{
}

bool WindowsInput::IsLBDown()
{
	return GetAsyncKeyState(VK_LBUTTON) < 0;
}

bool WindowsInput::IsKeyDown(char c)
{
	return GetAsyncKeyState(c) < 0;
}

bool WindowsInput::IsRBDown()
{
	return GetAsyncKeyState(VK_RBUTTON) < 0;
}

bool ZG::WindowsInput::IsMiddleDown()
{
	//std::cout << GetAsyncKeyState(VK_MBUTTON) << std::endl;
	return GetAsyncKeyState(VK_MBUTTON) < 0;
}

