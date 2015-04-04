#pragma once
#include "RenderEnum.h"
#include "RenderStateCollection.h"
#include "HardwareShader.h"
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
	void BuildShaderArgs(RasterRender* pRender, IRenderable* pRenderabl, shared_ptr<RasterMaterial> pMaterial, ESTAGESHADERTYPE eShaderType, HardwareVertexShader* pVertexShader, HardwareFragShader* pFragShader);
	void SetPassStates(RasterRender* pRender, const RenderStateCollection& mapStates);
	void SetShaderArgs(RasterRender* pRender,HardwareVertexShader* pVertexShader, HardwareFragShader* pFragShader);
	void SetBuiltInMatrixArg(RasterRender* pRender, IRenderable* pRenderable, std::unordered_map<string, MaterialArg*>& argToBuild, std::unordered_map<string, ShaderConstantInfo>& argIn);





	template<class T> 
	TMatArg<T>* GetArgFromLib(string strName, EMATARGTYPE eType);
protected:
	//for shader related arg only;
	//another args map in material
	std::unordered_map<string, MaterialArg*> m_ShaderArgs;
	std::vector<stRenderState> vecRenderState;

	//
	std::unordered_map<string, MaterialArg*> m_VertexShaderArgs;
	std::unordered_map<string, MaterialArg*> m_FragShaderArgs;
	//


	std::unordered_map<string, MaterialArg*> m_ArgLib;
public:
	EVERTEXSHADERTPYE	m_eVertexShaderType;
	EFRAGSHADERTYPE		m_eFragShaderType;

};

template<class T>
TMatArg<T>* RenderPass::GetArgFromLib(string strName, EMATARGTYPE eType)
{
	TMatArg<T>* pRet;
	if (m_ArgLib.find(strName) != std::end(m_ArgLib))
	{
		pRet = dynamic_cast<TMatArg<T>*>(m_ArgLib[strName]);
		return pRet;
	}
	pRet = new TMatArg<T>(eType);
	m_ArgLib[strName] = pRet;
	return pRet;
}

