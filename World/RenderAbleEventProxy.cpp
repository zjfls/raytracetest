#include "stdafx.h"
#include "RenderAbleEventProxy.h"

template class WORLD_API  Singleton < ZG::RenderAbleEventProxy >;
template<> SmartPointer<ZG::RenderAbleEventProxy> Singleton<ZG::RenderAbleEventProxy>::_instance = nullptr;

ZG::RenderAbleEventProxy::RenderAbleEventProxy()
{

}

ZG::RenderAbleEventProxy::~RenderAbleEventProxy()
{

}
