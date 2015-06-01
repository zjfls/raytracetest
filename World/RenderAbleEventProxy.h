#pragma once
#include "Event.h"
#include "Singleton.h"
#include "GameObjectBase.h"
class IRenderable;
namespace ZG
{
	class WORLD_API RenderableEventArgs
	{
	public:
		RenderableEventArgs(){};
		virtual ~RenderableEventArgs(){};
	public:
		SmartPointer<IRenderable> m_pRenderable;
	};
	class RenderAbleEventProxy:public Singleton<RenderAbleEventProxy>,public GameObjectBase
	{
	public:
		RenderAbleEventProxy();
		virtual ~RenderAbleEventProxy();
	};
	//
	extern template class WORLD_API  Singleton < RenderAbleEventProxy >;
}


