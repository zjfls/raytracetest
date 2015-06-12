#pragma once
#include "MaterialResource.h"
//#include "RenderPass.h"
#include "RenderEnum.h"
#include "SmartPointer.h"
namespace ZG
{

	class MaterialPass;
	struct stRenderState;


	class RenderPass;
	class RESOURCE_API RasterMaterial :
		public MaterialResource
	{
	public:
		RasterMaterial();
		virtual ~RasterMaterial();
		//void	AddPass(string strName, RenderPass* pPass);
		virtual SmartPointer<MaterialResource> clone();
		void AddPass(string strName, MaterialPass* pPass);

		void	SetRenderState(stRenderState& s);
		//void BuildPassParameter(RenderPass* pPass);
	public:
		//std::map<string, RenderPass*> m_RenderPassMap;
		//
		std::map<string, SmartPointer<MaterialPass>> m_MaterialPass;

		friend class RenderStage;
	};

}