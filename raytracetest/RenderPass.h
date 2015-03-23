#pragma once
#include "RenderEnum.h"
#include "RenderStateCollection.h"
class VertexShader;
class FragShader;
class RasterRender;

class RenderPass
{
public:
	RenderPass();
	virtual ~RenderPass();



	void Render(RasterRender* pRender, IRenderable* pRenderable, ESTAGESHADERTYPE eShaderType);
	shared_ptr<VertexShader> m_pVertexShader;
	shared_ptr<FragShader>	m_pFragShader;


	RenderStateCollection m_RenderState;

};

