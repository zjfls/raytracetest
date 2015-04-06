#pragma once
class FragShaderDesc;
class MAIN_API ShaderGenerator
{
public:
	ShaderGenerator();
	virtual ~ShaderGenerator();

	static const char* GetFragShader(const FragShaderDesc& pShader);
	static const char* ForwardGenSingleLight(const FragShaderDesc& pShader);

	static std::unordered_map<string, const char*> m_mapCode;
};

