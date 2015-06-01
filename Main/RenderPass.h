#pragma once
#include "RenderEnum.h"
#include "RenderStateCollection.h"
#include "HardwareShader.h"
#include "MaterialArg.h"
#include "MaterialPass.h"
#include "RenderBaseClass.h"
using ZG::stRenderState;
using ZG::MaterialPass;

class VertexShader;
class FragShader;
class RasterRender;
class RasterMaterial;
class IRenderable;
class HardwareFragShader;
class HardwareVertexShader;
class LightBase;
class FragShaderDesc;

class RenderPass
{
public:
	RenderPass(MaterialPass* pPass);
	RenderPass();
	virtual ~RenderPass();



	void Render(RasterRender* pRender, std::shared_ptr<IRenderable> pRenderable, ESTAGESHADERTYPE eShaderType, const RenderStateCollection& mapStates);
	shared_ptr<VertexShader> m_pVertexShader;
	shared_ptr<FragShader>	m_pFragShader;


	RenderStateCollection m_RenderState;//THE STATE SET FROM STAGE
	RenderPass*	clone();
private:
	//build args like matrix bone
	void BuildShaderArgs(RasterRender* pRender, std::shared_ptr<IRenderable> pRenderabl, shared_ptr<RasterMaterial> pMaterial, ESTAGESHADERTYPE eShaderType, HardwareVertexShader* pVertexShader, HardwareFragShader* pFragShader);
	void SetPassStates(RasterRender* pRender, const RenderStateCollection& mapStates);
	void SetShaderArgs(RasterRender* pRender,HardwareVertexShader* pVertexShader, HardwareFragShader* pFragShader);
	void SetBuiltInArgs(RasterRender* pRender, std::shared_ptr<IRenderable> pRenderable, std::unordered_map<string, MaterialArg*>& argToBuild, std::unordered_map<string, ShaderConstantInfo>& argIn);

	void SetPerLightArg(RasterRender* pRender, shared_ptr<LightBase> pLight, HardwareFragShader* pFragShader,FragShaderDesc& desc);



	template<class T> 
	TMatArg<T>* GetArgFromLib(string strName, EMATARGTYPE eType);
protected:
	//for shader related arg only;
	//another args map in material
	std::unordered_map<string, MaterialArg*> m_ShaderArgs;
	std::vector<stRenderState> m_vecRenderState;

	//
	std::unordered_map<string, MaterialArg*> m_VertexShaderArgs;
	std::unordered_map<string, MaterialArg*> m_FragShaderArgs;
	//
	std::unordered_map<string, MaterialArg*> m_ArgLib;
	MaterialPass*		m_MaterialPass;
public:
	EVERTEXSHADERTPYE	m_eVertexShaderType;
	EFRAGSHADERTYPE		m_eFragShaderType;
	
	friend class MaterialAssetLoader;


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

