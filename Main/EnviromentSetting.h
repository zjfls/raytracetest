#pragma once
class MAIN_API EnviromentSetting :public Singleton<EnviromentSetting>
{
public:
	EnviromentSetting();
	virtual ~EnviromentSetting();
	string	GetSetting(string strName);
	int		GetIntSetting(string name);
	float	GetFloatSetting(string name);

	bool	Init();
private:
	std::unordered_map<string, string> m_EnviromentSetting;
};

extern template class MAIN_API Singleton < EnviromentSetting > ;