#include "stdafx.h"
#include "EditorCommandManager.h"
#include "ICommand.h"

template class EDITOR_API Singleton < EditorCommandManager >;
template<> SmartPointer<EditorCommandManager> Singleton<EditorCommandManager>::_instance = nullptr;

ZG::EditorCommandManager::EditorCommandManager()
	:m_nCmdSize(100)
	, m_nCurIndex(0)
{
	//m_Cmds.resize(100);
}

ZG::EditorCommandManager::~EditorCommandManager()
{

}

void ZG::EditorCommandManager::ExcuteNewCmd(ICommand* pCmd)
{
	if (m_Cmds.size() >= m_nCmdSize)
	{
		RemoveCmdFrond();
	}
	//
	m_Cmds.push_back(pCmd);
	pCmd->excute();
	m_nCurIndex = m_Cmds.size();

}

void ZG::EditorCommandManager::Undo()
{
	if (m_Cmds.size() <= 0 || m_nCurIndex == 0)
	{
		return;
	}
	//
	ICommand* pCmd = m_Cmds[m_nCurIndex - 1];
	pCmd->undo();
	m_nCurIndex -= 1;
	
}

void ZG::EditorCommandManager::Redo()
{
	if (m_Cmds.size() <= 0 || m_nCurIndex == m_Cmds.size())
	{
		return;
	}
	//
	ICommand* pCmd = m_Cmds[m_nCurIndex];
	pCmd->redo();
	m_nCurIndex += 1;
}

void ZG::EditorCommandManager::RemoveCmdFrond()
{
	if (m_Cmds.size() <= 0)
	{
		return;
	}
	ICommand* pCmd = m_Cmds.front();
	delete pCmd;
	m_Cmds.pop_front();
	m_nCurIndex -= 1;
}
