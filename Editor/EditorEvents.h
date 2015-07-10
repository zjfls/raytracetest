#pragma once
#include "Event.h"
namespace ZG
{
	class IWorldObj;
	class AddSceneGraphEventArg
	{
	public:
		AddSceneGraphEventArg(){};
		virtual ~AddSceneGraphEventArg(){};

		IWorldObj* m_pObj;
		IWorldObj* m_pParent;

	};

	class DeleteSceneGraphEventArg
	{
	public:
		DeleteSceneGraphEventArg(){};
		virtual ~DeleteSceneGraphEventArg(){};

		IWorldObj* m_pObj;
		IWorldObj* m_pParent;
	};

	class SceneGraphSelChangeArg
	{
	public:
		SceneGraphSelChangeArg(){};
		virtual ~SceneGraphSelChangeArg(){};

		//IWorldObj* m_pObj;
		std::vector<IWorldObj*> m_vecObjs;
	};
	class EditorUpdateArg
	{
	public:
		EditorUpdateArg(){};
		virtual ~EditorUpdateArg(){};
	};
}
