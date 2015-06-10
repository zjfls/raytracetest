#pragma once
namespace ZG
{
	class FragShaderDesc;
	class MAIN_API ShaderGenerator
	{
	public:
		ShaderGenerator();
		virtual ~ShaderGenerator();

		static const char* GetFragShader(FragShaderDesc& pShader);
		static const char* ForwardGenSingleLight(FragShaderDesc& pShader);

		static std::unordered_map<string, const char*> m_mapCode;
		static std::vector<string> m_vecPPParam;


		static void PreProcessShader(char* pCode, unsigned int nLength, std::unordered_map<std::string, bool>& map);
	private:
		static void RemoveComment(char* pCode, unsigned int nLength);
	};

}