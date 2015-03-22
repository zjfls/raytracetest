#include "stdafx.h"
#include "EnviromentSetting.h"
EnviromentSetting* Singleton<EnviromentSetting>::_instance = nullptr;

EnviromentSetting::EnviromentSetting()
{
}


EnviromentSetting::~EnviromentSetting()
{
}

std::string EnviromentSetting::GetSetting(string strName)
{
	return m_EnviromentSetting[strName];
}

int EnviromentSetting::GetIntSetting(string name)
{
	string strValue = m_EnviromentSetting[name];
	//char temp[25];
	int nValue = atoi(strValue.c_str());
	return nValue;
}

float EnviromentSetting::GetFloatSetting(string name)
{
	string strValue = m_EnviromentSetting[name];
	//char temp[25];
	float fValue = atof(strValue.c_str());
	return fValue;
}

bool EnviromentSetting::Init()
{
	m_EnviromentSetting["RenderType"] = "D3D9";
	return true;
}
