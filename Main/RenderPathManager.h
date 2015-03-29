#pragma once


class RenderPath;
class RenderPathManager:public Singleton<RenderPathManager>
{
public:
	RenderPathManager();
	~RenderPathManager();
	//
	bool Init();
	//
	RenderPath* GetRenderPath(string strName);
	//
	void		AddRenderPath(string strName,RenderPath* pPath);
private:
	std::map<string, RenderPath*> m_mapRenderPath;
};

