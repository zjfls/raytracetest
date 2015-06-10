#pragma once
#include "Singleton.h"
#include "GameObjectBase.h"

namespace ZG
{
	class IndexData;
	class VertexData;
	class IndexDataEventArg :public GameObjectBase
	{
	public:
		IndexDataEventArg(){};
		virtual ~IndexDataEventArg(){};


		IndexData* m_pIndexData;
	};
	class VertexDataEventArg
	{
	public:
		VertexDataEventArg(){};
		virtual ~VertexDataEventArg(){};

		VertexData* m_pVertexData;
	};
	class FOUNDATION_API VertexIndexDataEventProxy :public Singleton<VertexIndexDataEventProxy>,public GameObjectBase
	{
	public:
		VertexIndexDataEventProxy();
		virtual ~VertexIndexDataEventProxy();
		//
		//
	};
	extern template class FOUNDATION_API  Singleton < VertexIndexDataEventProxy >;
}


