#pragma once
class IRenderable;
class LightBase;
class IWorld
{
public:
	IWorld();
	virtual ~IWorld();


	IWorldObj* m_pRoot;
	static IWorld* pSingleWorld;
	void Update();

	std::vector<IRenderable*> GetAllRenderables();

	template<class T>
	std::vector<T*> GetAllComponent();
};

template<class T>
std::vector<T*>
IWorld::GetAllComponent()
{
	std::vector<T*> vecModules;
	m_pRoot->GetAllModuleRecursive<T>(vecModules);
	return vecModules;
}

