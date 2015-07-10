#pragma once
#include "ICommand.h"
#include "IWorldObj.h"
#include "Vector3.h"
#include <vector>
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
		std::vector<SmartPointer<IWorldObj>> m_vecObjs;
		//SmartPointer<IWorldObj> m_pObj;
		//SmartPointer<IWorldObj> m_pParentObj;
		std::vector<SmartPointer<IWorldObj>> m_vecParentObjs;
	};
	class EDITOR_API AddToSceneCommand :public ICommand
	{
	public:
		AddToSceneCommand(){};
		virtual ~AddToSceneCommand(){};

		std::vector<SmartPointer<IWorldObj>> m_vecObjs;
		//SmartPointer<IWorldObj> m_pObj;
		//SmartPointer<IWorldObj> m_pParentObj;
		std::vector<SmartPointer<IWorldObj>> m_vecParentObjs;
	};
	class EDITOR_API MoveCommand :public ICommand
	{
	public:
		MoveCommand(){};
		virtual ~MoveCommand(){};
		//SmartPointer<IWorldObj> m_pObj;
		//Vector3 m_vecPrePos;
		//Vector3 m_vecNextPos;


		std::vector<Vector3> m_vecPrePos;
		std::vector<Vector3> m_vecNextPos;
		std::vector<SmartPointer<IWorldObj>> m_vecObjs;
	};
}

