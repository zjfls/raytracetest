#pragma once
#include "Color.h"
class MAIN_API EnviromentSetting :public Singleton<EnviromentSetting>
{
public:
	EnviromentSetting();
	virtual ~EnviromentSetting();
	string	GetSetting(string strName);
	int		GetIntSetting(string name);
	float	GetFloatSetting(string name);




	bool	Init();
	Color	GetAmbientColor() const { return m_AmbientColor; };
private:
	std::unordered_map<string, string> m_EnviromentSetting;
	Color	m_AmbientColor;
};

extern template class MAIN_API Singleton < EnviromentSetting > ;