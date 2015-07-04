#pragma once
namespace ZG
{
	class MAIN_API IResource :public GameObjectBase
	{
	public:
		IResource();
		virtual ~IResource();

		std::string GetRefPath()const{ return m_refPath; }

	protected:
		std::string m_refPath;
		//public:
		//	string m_Name;
	};
}


