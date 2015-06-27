#pragma once
#include "Singleton.h"
#include <deque>
#include "ICommand.h"
namespace ZG
{
	class ICommand;
	class EDITOR_API EditorCommandManager:public GameObjectBase,public Singleton<EditorCommandManager>
	{
	public:
		EditorCommandManager();
		virtual ~EditorCommandManager();
		void ExcuteNewCmd(ICommand* pCmd);
		void Undo();
		void Redo();
	private:
		void RemoveCmdFrond();
	private:
		//std::deque<ICommand*> m_dequeCmds;
		int m_nCmdSize;
		int m_nCurIndex;
		std::deque<ICommand*> m_Cmds;
	};

	extern template  class EDITOR_API  Singleton < EditorCommandManager >;
}


