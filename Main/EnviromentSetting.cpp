#include "stdafx.h"
#include "EnviromentSetting.h"
#include "tinyxml2.h"
using namespace tinyxml2;
template class MAIN_API Singleton < EnviromentSetting >;
template<> shared_ptr<EnviromentSetting> Singleton<EnviromentSetting>::_instance = nullptr;

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
	float fValue = (float)atof(strValue.c_str());
	return fValue;
}

bool EnviromentSetting::Init()
{
	//m_EnviromentSetting["RenderType"] = "D3D9";
	XMLDocument doc;
	doc.LoadFile("./data/config/EnvSettings.xml");
	XMLElement* pConfig = doc.FirstChildElement("CONFIG");
	if (pConfig == nullptr)
	{
		return false;
	}
	XMLElement* pSetting = pConfig->FirstChildElement("Setting");
	while (pSetting != nullptr)
	{
		string name = pSetting->Attribute("Name");
		string value = pSetting->Attribute("Value");
		m_EnviromentSetting[name] = value; 
		std::cout << name.c_str() << ":" << value.c_str() << std::endl;
		pSetting = pSetting->NextSiblingElement("Setting");
	}
	XMLElement* pAmbient = pConfig->FirstChildElement("AmbientColor");
	m_AmbientColor.m_fA = pAmbient->FloatAttribute("a");
	m_AmbientColor.m_fR = pAmbient->FloatAttribute("r");
	m_AmbientColor.m_fG = pAmbient->FloatAttribute("g");
	m_AmbientColor.m_fB = pAmbient->FloatAttribute("b");
	return true;
}
