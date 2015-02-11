#pragma once
class IWorld
{
public:
	IWorld();
	virtual ~IWorld();


	IWorldObj* m_pRoot;
	static IWorld* pSingleWorld;
	static void Update();
};

