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
		RenderPath* GetRenderPath(string strName);
		//
		void		AddRenderPath(string strName, RenderPath* pPath);
		//
		//bool		InitPathBuffer();
	private:
		std::map<string, RenderPath*> m_mapRenderPath;
	};

}