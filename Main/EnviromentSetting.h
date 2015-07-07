#pragma once
#include "Color.h"
namespace ZG
{
	class MAIN_API EnviromentSetting :public Singleton<EnviromentSetting>, public GameObjectBase
	{
	public:
		EnviromentSetting();
		virtual ~EnviromentSetting();
		std::string	GetSetting(std::string strName);
		int		GetIntSetting(std::string name);
		float	GetFloatSetting(std::string name);




		bool	Init();
		GameColor	GetAmbientColor() const { return m_AmbientColor; };
	private:
		std::unordered_map<std::string, std::string> m_EnviromentSetting;
		GameColor	m_AmbientColor;
	};

	extern template class MAIN_API Singleton < EnviromentSetting > ;
}