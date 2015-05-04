#pragma once
class IRenderable;
class LightBase;
class IWorldObj;
class WORLD_API IWorld
{
public:
	IWorld();
	virtual ~IWorld();
	

	shared_ptr<IWorldObj> m_pRoot;
	void Update();

	std::vector<shared_ptr<IRenderable>> GetAllRenderables();
	virtual void GetRenderablesLightInfo(std::vector<shared_ptr<IRenderable>>& vec);



	template<class T>
	std::vector<shared_ptr<T>> GetAllModules();


	
};

template<class T>
std::vector<shared_ptr<T>>
IWorld::GetAllModules()
{
	std::vector<shared_ptr<T>> vecModules;
	m_pRoot->GetAllModuleRecursive<T>(vecModules);
	return vecModules;
}

