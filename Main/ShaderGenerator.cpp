#include "stdafx.h"
#include "ShaderGenerator.h"
#include "FragShader.h"
std::unordered_map<string, const char*> ShaderGenerator::m_mapCode;

ShaderGenerator::ShaderGenerator()
{
}


ShaderGenerator::~ShaderGenerator()
{
}

const char* ShaderGenerator::ForwardGenSingleLight(const FragShaderDesc& pShader)
{
	string rtCode = "";
	if (pShader.m_eLightType == EPOINTLIGHT)
	{
		rtCode += "float3 VIEW_POS;\n";
	}
	rtCode = m_mapCode["lightatten"];
	rtCode += "\n";
	rtCode += m_mapCode["surfaceblinnphong"];
	rtCode += "\n";
	rtCode += pShader.m_pFragShader->m_pCodeBuffer;
	rtCode += "\n";
	if (pShader.m_eLightType == EDIRLIGHT)
	{
		rtCode += "float3 GAMELIGHTDIR;\n";
	}
	rtCode += "float GAMELIGHTINTENSITY;\n"\
		"float3 GAMELIGHTCOLOR;\n";

	if (pShader.m_eLightType == EPOINTLIGHT)
	{
		rtCode += "float3 GAMELIGHTPOS;\n";
	}

	rtCode += "float4 pMain(PS_INPUT input):Color0\n"	\
		"{\n"									\
		"	//input = (PS_INPUT)0;\n"\
		"	SurfaceOutput o = Surface(input);\n";
		//"#ifdef POINTLIGHT";
		//"float atten = lightPointAtten(lightPos);"\
		//"#endif"\
		//"#ifdef SPOTLIGHT"\
		//"float atten = lightSpotAtten(lightPos);"\
		//"#endif"\
		//"#ifdef DIRLIGHT"\
		//"float atten = 1;"\
		//"#endif"\
		
	if (pShader.m_eLightType == EDIRLIGHT)
	{
		rtCode += "float atten = 1;\n";
		rtCode += "float3 lightdir = normalize(GAMELIGHTDIR);\n";
		rtCode += "lightdir = normalize(lightdir);\n";
	}
	else if (pShader.m_eLightType == EPOINTLIGHT)
	{
		rtCode += "float atten = lightPointAtten(GAMELIGHTPOS,input.worldPosition);\n";
		rtCode += "float3 lightdir = normalize(GAMELIGHTDIR);\n";
	}
	rtCode += "float4 Color;\n"\
		"Color.rgb = CalLight(o,atten,input.WorldEyeVec,lightdir,GAMELIGHTINTENSITY,GAMELIGHTCOLOR).rgb;\n"\
		"Color.a = o.Alpha;\n"\
		"return Color;\n"\
		"}\n";


	int nLength = rtCode.length();
	char* temp = new char[nLength + 1];
	strcpy_s(temp,nLength + 1, rtCode.c_str());
	temp[nLength] = 0;
	
	return temp;
}

const char* ShaderGenerator::GetFragShader(const FragShaderDesc& pShader)
{
	if (pShader.m_eStageDesc == ESTAGESHADERRADIANCEONLIGHTING)
	{
		return ForwardGenSingleLight(pShader);
	}
	else if (pShader.m_eStageDesc == ESTAGESHADERRADIANCEALLLIGHTING)
	{

	}
	return nullptr;
}

