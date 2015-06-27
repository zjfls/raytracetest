#pragma once
#include "ICommand.h"
#include "IWorldObj.h"
namespace ZG
{
	class IWorldObj;
	class EDITOR_API DeleteCommand :public ICommand
	{
	public:
		DeleteCommand();
		virtual ~DeleteCommand(){};

		//bool excute() override;
		//bool undo() override;
		//bool redo() override;
		//
		SmartPointer<IWorldObj> m_pObj;
		SmartPointer<IWorldObj> m_pParentObj;
	};
	class EDITOR_API AddToSceneCommand :public ICommand
	{
	public:
		AddToSceneCommand(){};
		virtual ~AddToSceneCommand(){};

		SmartPointer<IWorldObj> m_pObj;
		SmartPointer<IWorldObj> m_pParentObj;
	};
}

