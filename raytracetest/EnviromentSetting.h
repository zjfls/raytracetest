#pragma once
class EnviromentSetting:public Singleton<EnviromentSetting>
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

