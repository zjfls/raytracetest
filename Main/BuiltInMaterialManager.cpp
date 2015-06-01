#include "stdafx.h"
#include "BuiltInMaterialManager.h"
#include "RasterMaterial.h"
#include "RenderPass.h"
#include "AssetManager.h"
#include "VertexShader.h"
#include "FragShader.h"
#include "MaterialPass.h"
using namespace ZG;
template class MAIN_API  Singleton < BuiltInMaterialManager >;
template<> shared_ptr<BuiltInMaterialManager> Singleton<BuiltInMaterialManager>::_instance = nullptr;

BuiltInMaterialManager::BuiltInMaterialManager()
{
}


BuiltInMaterialManager::~BuiltInMaterialManager()
{
}

bool BuiltInMaterialManager::InitBuiltInMaterial()
{
	CreateDefaultMaterial();
	return true;
}

void BuiltInMaterialManager::CreateDefaultMaterial()
{
	shared_ptr<RasterMaterial> pMat(new RasterMaterial);
	shared_ptr<RasterMaterial> pMatRes = ResourceManager<MaterialResource>::GetInstance()->CreateResource<RasterMaterial>("GAMEDEFAULTMATERIAL");
	MaterialPass* pPass = new MaterialPass();
	TMatArg<GameColor>* pArg = new TMatArg<GameColor>(EMATARGTYPECOLOR);
	pArg->m_Data = GameColor::white;
	pMatRes->AddArg("MainColor", pArg);
	pMatRes->AddPass("First",pPass);
	AssetManager::GetInstance()->LoadAsset("./data/shader/builtin/Default.vsm");
	AssetManager::GetInstance()->LoadAsset("./data/shader/builtin/Default.fsm");
	pPass->m_eVertexShaderType = EVERTEXSHADERORIGIN;
	pPass->m_eFragShaderType = EFRAGSHADERORIGIN;
	pPass->m_pVertexShader = ResourceManager<VertexShader>::GetInstance()->GetResource("./data/shader/builtin/Default.vsm");
	pPass->m_pFragShader = ResourceManager<FragShader>::GetInstance()->GetResource("./data/shader/builtin/Default.fsm");
	

}
