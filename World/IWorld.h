#pragma once
class IRenderable;
class LightBase;
class IWorldObj;
class WORLD_API IWorld:public GameObjectBase
{
public:
	IWorld();
	virtual ~IWorld();
	

	SmartPointer<IWorldObj> m_pRoot;
	void Update();

	std::vector<SmartPointer<IRenderable>> GetAllRenderables();
	virtual void GetRenderablesLightInfo(std::vector<SmartPointer<IRenderable>>& vec);



	template<class T>
	std::vector<SmartPointer<T>> GetAllModules();


	
};

template<class T>
std::vector<SmartPointer<T>>
IWorld::GetAllModules()
{
	std::vector<SmartPointer<T>> vecModules;
	m_pRoot->GetAllModuleRecursive<T>(vecModules);
	return vecModules;
}

