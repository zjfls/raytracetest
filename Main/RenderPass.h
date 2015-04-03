#pragma once
#include "RenderEnum.h"
#include "RenderStateCollection.h"
class VertexShader;
class FragShader;
class RasterRender;
class RasterMaterial;
#include "MaterialArg.h"
class IRenderable;
class HardwareFragShader;
class HardwareVertexShader;

struct stRenderState
{
	RENDERSTATEMASK m_eRenderState;
	int				m_nValue;
};
class RenderPass
{
public:
	RenderPass();
	virtual ~RenderPass();



	void Render(RasterRender* pRender, IRenderable* pRenderable, ESTAGESHADERTYPE eShaderType, const RenderStateCollection& mapStates);
	shared_ptr<VertexShader> m_pVertexShader;
	shared_ptr<FragShader>	m_pFragShader;


	RenderStateCollection m_RenderState;//THE STATE SET FROM STAGE

private:
	//build args like matrix bone
	void BuildShaderArgs(RasterRender* pRender, IRenderable* pRenderabl, ESTAGESHADERTYPE eShaderType, HardwareVertexShader* pVertexShader,HardwareFragShader* pFragShader);
	void SetPassStates(RasterRender* pRender, const RenderStateCollection& mapStates);
	void SetShaderArgs(RasterRender* pRender, shared_ptr<RasterMaterial> pMaterial,HardwareVertexShader* pVertexShader,HardwareFragShader* pFragShader);
protected:
	//for shader related arg only;
	//another args map in material
	std::unordered_map<string, MaterialArg*> m_ShaderArgs;
	std::vector<stRenderState> vecRenderState;

	//
	std::unordered_map<string, MaterialArg> m_VertexShaderArgs;
	std::unordered_map<string, MaterialArg> m_FragShaderArgs;
	//
public:
	EVERTEXSHADERTPYE	m_eVertexShaderType;
	EFRAGSHADERTYPE		m_eFragShaderType;

};

