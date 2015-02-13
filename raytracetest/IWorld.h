#pragma once
class IRenderable;
class IWorld
{
public:
	IWorld();
	virtual ~IWorld();


	IWorldObj* m_pRoot;
	static IWorld* pSingleWorld;
	void Update();

	std::vector<IRenderable*> GetAllRenderables();
};

