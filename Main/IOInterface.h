#pragma once
namespace ZG
{
	class MAIN_API InputInterface:public GameObjectBase
	{
	public:
		InputInterface();
		virtual ~InputInterface();

		virtual bool IsLBDown() = 0;
		virtual bool IsRBDown() = 0;
		virtual bool IsMiddleDown() = 0;
		virtual bool IsKeyDown(char c) = 0;
	};

}