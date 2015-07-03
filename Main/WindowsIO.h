#pragma once
#include "IOInterface.h"
namespace ZG
{
	class WindowsInput :
		public InputInterface
	{
	public:
		WindowsInput();
		virtual ~WindowsInput();


		virtual bool IsLBDown();
		virtual bool IsRBDown();
		bool IsMiddleDown() override;
		virtual bool IsKeyDown(char c);
	};
}

