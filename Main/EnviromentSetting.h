#pragma once
#include "Color.h"
namespace ZG
{
	class MAIN_API EnviromentSetting :public Singleton<EnviromentSetting>, public GameObjectBase
	{
	public:
		EnviromentSetting();
		virtual ~EnviromentSetting();
		string	GetSetting(string strName);
		int		GetIntSetting(string name);
		float	GetFloatSetting(string name);




		bool	Init();
		GameColor	GetAmbientColor() const { return m_AmbientColor; };
	private:
		std::unordered_map<string, string> m_EnviromentSetting;
		GameColor	m_AmbientColor;
	};

	extern template class MAIN_API Singleton < EnviromentSetting > ;
}