#pragma once
#include "InputInterface.h"
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
		//int	 GetMouseWheel() override;
		virtual bool IsKeyDown(char c);
	};
}

