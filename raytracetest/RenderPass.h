#pragma once

class VertexShader;
class FragShader;
class RenderPass
{
public:
	RenderPass();
	virtual ~RenderPass();

	shared_ptr<VertexShader> m_pVertexShader;
	shared_ptr<FragShader>	m_pFragShader;
};

