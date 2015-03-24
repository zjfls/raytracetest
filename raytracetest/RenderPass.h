#pragma once
#include "RenderEnum.h"
#include "RenderStateCollection.h"
class VertexShader;
class FragShader;
class RasterRender;
class RasterMaterial;
#include "MaterialArg.h"


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


	RenderStateCollection m_RenderState;

private:
	//build args like matrix bone
	void BuildShaderArgs(RasterRender* pRender, IRenderable* pRenderabl, ESTAGESHADERTYPE eShaderType);
	void SetPassStates(RasterRender* pRender, const RenderStateCollection& mapStates);
	void SetShaderArgs(RasterRender* pRender, shared_ptr<RasterMaterial> pMaterial);
protected:
	//for shader related arg only;
	//another args map in material
	std::unordered_map<string, MaterialArg*> m_ShaderArgs;
	std::vector<stRenderState> vecRenderState;

};

