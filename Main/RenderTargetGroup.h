#pragma once
#include <map>
class IRenderTarget;
class MAIN_API RenderTargetGroup
{
public:
	RenderTargetGroup();
	virtual ~RenderTargetGroup();
	//
	void	SetRenderTarget(int nIndex,IRenderTarget* pTarget);

	std::map<int, IRenderTarget*> m_Map;
};

