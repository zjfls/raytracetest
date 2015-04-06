#pragma once
class IRenderable;
class LightBase;
class IWorldObj;
class WORLD_API IWorld
{
public:
	IWorld();
	virtual ~IWorld();
	

	IWorldObj* m_pRoot;
	void Update();

	std::vector<IRenderable*> GetAllRenderables();
	virtual void GetRenderablesLightInfo(std::vector<IRenderable*>& vec);



	template<class T>
	std::vector<T*> GetAllModules();


	
};

template<class T>
std::vector<T*>
IWorld::GetAllModules()
{
	std::vector<T*> vecModules;
	m_pRoot->GetAllModuleRecursive<T>(vecModules);
	return vecModules;
}

