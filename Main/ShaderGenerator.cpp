#include "stdafx.h"
#include "ShaderGenerator.h"
#include "FragShader.h"
#include <memory>
std::unordered_map<string, const char*> ShaderGenerator::m_mapCode;
std::vector<string> ShaderGenerator::m_vecPPParam;
ShaderGenerator::ShaderGenerator()
{
}


ShaderGenerator::~ShaderGenerator()
{
}

const char* ShaderGenerator::ForwardGenSingleLight(FragShaderDesc& pShader)
{
	string rtCode = "";
	if (pShader.m_bAmbient == true)
	{
		rtCode += "float4 GAMEAMBIENTCOLOR;\n";
	}
	if (pShader.m_eLightType == EDIRLIGHT)
	{
		rtCode += "float3 GAMELIGHTDIR;\n";
	}
	rtCode += "float GAMELIGHTINTENSITY;\n"\
		"float4 GAMELIGHTCOLOR;\n";

	if (pShader.m_eLightType == EPOINTLIGHT)
	{
		rtCode += "float3 GAMELIGHTPOS;\n";
	}


	//
	//if (pShader.m_pFragShader->m_mapEngineParam["VIEW_POS"] != false)
	{
		rtCode += "float3 VIEW_POS;\n";
	}
	rtCode += m_mapCode["lightatten"];
	rtCode += "\n";
	rtCode += m_mapCode["surfaceblinnphong"];
	rtCode += "\n";
	rtCode += pShader.m_pFragShader->m_pCodeBuffer;
	rtCode += "\n";
	rtCode += "float4 pMain(PS_INPUT input):Color0\n"	\
		"{\n"									\
		"	//input = (PS_INPUT)0;\n"\
		"	SurfaceOutput o = Surface(input);\n";		
	if (pShader.m_eLightType == EDIRLIGHT)
	{
		rtCode += "float atten = 1;\n";
		rtCode += "float3 lightdir = normalize(GAMELIGHTDIR);\n";
		//rtCode += "lightdir = normalize(lightdir);\n";
	}
	else if (pShader.m_eLightType == EPOINTLIGHT)
	{
		rtCode += "float atten = lightPointAtten(GAMELIGHTPOS,input.worldPosition);\n";
		rtCode += "float3 lightdir = GAMELIGHTPOS - input.worldPosition;\n";
		rtCode += "lightdir = normalize(lightdir);\n";
	}
	rtCode += "float4 Color;\n"\
		"float3 eyevec = normalize(VIEW_POS - input.worldPosition);\n"\
		"Color.rgb = CalLight(o,atten,eyevec,lightdir,GAMELIGHTINTENSITY,GAMELIGHTCOLOR.rgb).rgb;\n";
	if (pShader.m_bAmbient == true)
	{
		rtCode += "Color.rgb += o.DiffuseColor * GAMEAMBIENTCOLOR;\n";
	}
	rtCode += "Color.a = o.Alpha;\n"\
		"return Color;\n"\
		"}\n";
	//rtCode += m_mapCode["debug"];


	int nLength = rtCode.length();
	char* temp = new char[nLength + 1];
	strcpy_s(temp, nLength + 1, rtCode.c_str());
	temp[nLength] = 0;
	//std::cout << temp << std::endl;
	return temp;
}

const char* ShaderGenerator::GetFragShader(FragShaderDesc& pShader)
{
	if (pShader.m_eStageDesc == ESTAGESHADER_RADIANCE_ONELIGHTING)
	{
		return ForwardGenSingleLight(pShader);
	}
	else if (pShader.m_eStageDesc == ESTAGESHADERRADIANCEALLLIGHTING)
	{

	}
	return nullptr;
}

void ShaderGenerator::PreProcessShader(char* pCode, unsigned int nLength, std::unordered_map<std::string, bool>& map)
{
	RemoveComment(pCode, nLength);

	for each (std::string param in m_vecPPParam)
	{
		if (strstr(pCode, param.c_str()) != nullptr)
		{
			map[param] = true;
		}
	}
}

void ShaderGenerator::RemoveComment(char* pCode, unsigned int nLength)
{
	bool bComment1 = false;
	bool bComment2 = false;
	char* pIdx = pCode;
	for (unsigned int i = 0; i < nLength - 1; ++i)
	{
		if (bComment1 == true)
		{
			if (pCode[i] == '\n')
			{
				bComment1 = false;
				continue;
			}
			pCode[i] = ' ';
			continue;
		}
		else if (bComment2 == true)
		{
			if (pCode[i] == '*' && pCode[i + 1] == '/')
			{
				pCode[i] = ' ';
				i++;
				bComment2 = false;
			}
			pCode[i] = ' ';
			continue;
		}
		if (pCode[i] == '/')
		{
			if (pCode[i + 1] == '/')
			{
				bComment1 = true;
				pCode[i] = ' ';
			}
			else if (pCode[i + 1] == '*')
			{
				bComment2 = true;
				pCode[i] = ' ';
			}
		}
	}

}

