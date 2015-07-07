#pragma once

namespace ZG
{
	class RenderPath;
	class RenderPathManager :public Singleton<RenderPathManager>, public GameObjectBase
	{
	public:
		RenderPathManager();
		~RenderPathManager();
		//
		bool Init();
		//
		RenderPath* GetRenderPath(std::string strName);
		//
		void		AddRenderPath(std::string strName, RenderPath* pPath);
		//
		//bool		InitPathBuffer();
	private:
		std::map<std::string, RenderPath*> m_mapRenderPath;
	};

}