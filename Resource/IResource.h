#pragma once
class RESOURCE_API IResource
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
