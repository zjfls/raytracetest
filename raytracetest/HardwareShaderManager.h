#pragma once


class HardwareVertexShader;
class HardwareFragShader;
class HardwareShaderManager:public Singleton<HardwareShaderManager>
{
public:
	HardwareShaderManager();
	virtual ~HardwareShaderManager();

	std::unordered_map<string, HardwareVertexShader*> m_mapHardwareVertexShader;
	std::unordered_map<string, HardwareFragShader*> m_mapHardwareFragShader;
};

