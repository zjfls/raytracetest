#include "stdafx.h"
#include "IWorld.h"
IWorld* IWorld::pSingleWorld = nullptr;

IWorld::IWorld()
{
	m_pRoot = new IWorldObj();
}


IWorld::~IWorld()
{
}

void IWorld::Update()
{

}
