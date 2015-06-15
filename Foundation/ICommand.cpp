#include "stdafx.h"
#include "ICommand.h"
#include "IReceiver.h"

ZG::ICommand::ICommand()
{

}

ZG::ICommand::~ICommand()
{

}

bool ZG::ICommand::excute()
{
	return m_pReceiver->excuteCommond(this);
}

bool ZG::ICommand::undo()
{
	return m_pReceiver->undoCommond(this);
}

bool ZG::ICommand::redo()
{
	return m_pReceiver->redoCommond(this);
}
