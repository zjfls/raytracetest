#pragma once
namespace ZG
{
	class RESOURCE_API IResource :public GameObjectBase
	{
	public:
		IResource();
		virtual ~IResource();

		string GetRefPath()const{ return m_refPath; }

	protected:
		string m_refPath;
		//public:
		//	string m_Name;
	};
}


