#pragma once
#include "Event.h"
#include "Singleton.h"
#include "GameObjectBase.h"
#include "IRenderable.h"
class IRenderable;
namespace ZG
{
	class MAIN_API RenderableEventArgs
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
	extern template class MAIN_API  Singleton < RenderAbleEventProxy >;
}


