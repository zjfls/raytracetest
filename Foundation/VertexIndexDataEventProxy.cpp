#include "stdafx.h"
#include "VertexIndexDataEventProxy.h"

template class FOUNDATION_API  Singleton < ZG::VertexIndexDataEventProxy >;
template<> SmartPointer<ZG::VertexIndexDataEventProxy> Singleton<ZG::VertexIndexDataEventProxy>::_instance = nullptr;
//
ZG::VertexIndexDataEventProxy::VertexIndexDataEventProxy()
{
	addEvent("INDEXDATADELETE", new Event<IndexDataEventArg>());
	addEvent("VERTEXDATADELETE", new Event<VertexDataEventArg>());
}

//
ZG::VertexIndexDataEventProxy::~VertexIndexDataEventProxy()
{

}
