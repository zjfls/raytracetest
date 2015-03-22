#pragma once
struct stRenderViewInfo;
class IRender;
class RenderView;
class RenderPath;
class RenderSystem
{
public:
	~RenderSystem();
	virtual IRender* GetDefaultRender() const = 0;
	virtual RenderView* GetDefaultRenderView() const = 0;	
	virtual bool InitRenderSystem(const stRenderViewInfo& viewInfo) const = 0;
protected:
	virtual void	CreateDefaultRender(const RenderPath* pPath) const = 0;
	RenderSystem();
	friend class RenderManager;
};

