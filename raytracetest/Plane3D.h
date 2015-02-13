#pragma once
class Plane3D:public ModuleBase
{
public:
	//Plane3D();
	Plane3D(const Point3D& vecPt,const Direction3D& vecNormal);
	virtual ~Plane3D();

	Point3D m_vecPt;
	Direction3D m_vecNormal;
private:
	Plane3D();
	friend class IWorldObj;
};

//class Plane3DCreator :public IModuleCreator
//{
//public:
//	Plane3DCreator();
//	virtual ~Plane3DCreator();
//
//	virtual ModuleBase* CreateModule();
//
//};

