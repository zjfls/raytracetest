#pragma once

namespace ZG
{
	class IReceiver;
	class FOUNDATION_API ICommand
	{
	public:
		ICommand();
		virtual ~ICommand();
		//
		virtual bool excute();
		virtual bool undo();
		virtual bool redo();
		//

		IReceiver* m_pReceiver;
	};
}


