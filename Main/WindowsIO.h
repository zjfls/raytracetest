#pragma once
#include "IOInterface.h"
class WindowsIO :
	public IOInterface
{
public:
	WindowsIO();
	virtual ~WindowsIO();


	virtual bool IsLBDown();
	virtual bool IsRBDown();
	virtual bool IsKeyDown(char c);
};

