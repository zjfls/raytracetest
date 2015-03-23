#pragma once
#include "IResource.h"
#include "RenderEnum.h"

class VertexShaderDesc
{
public:
	ESTAGESHADERTYPE m_eStageDesc;
	bool			m_bSkinInfo;
	int				m_bSkinNum;
};
class HardwareVertexShader;
class VertexShader:public IResource
{
public:
	VertexShader();
	virtual ~VertexShader();


	HardwareVertexShader* GetHardwareVertexShader(const VertexShaderDesc& vertexShaderDesc) const;
	static HardwareVertexShader* GetHardwareVertexShaderByDesc(const VertexShaderDesc& vertexShaderDesc);
};

