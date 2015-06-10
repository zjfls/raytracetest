#pragma once
#include "IOInterface.h"
namespace ZG
{
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
}

