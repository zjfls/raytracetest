#pragma once

namespace ZG
{
	class ICommand;
	class FOUNDATION_API IReceiver
	{
	public:
		IReceiver();
		virtual ~IReceiver();
		//

		virtual bool excuteCommond(ICommand* pCommand) = 0;
		virtual bool undoCommond(ICommand* pCommond) = 0;
		virtual bool redoCommond(ICommand* pCommond) = 0;
	};
}


