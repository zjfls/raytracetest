#pragma once
#include "IRender.h"
#include "RenderStage.h"
class RenderPath;
class IRenderable;
class RasterRender :
	public IRender
{
public:
	/*RasterRender();*/
	RasterRender(const RenderPath* pPath);
	virtual ~RasterRender();
	//render a obj
	virtual void Render(IRenderable* pRender);
	virtual int Render(std::vector<IRenderable*>& pRenderableList);
	virtual int Render(CameraBase* pCammera, IWorld* pWorld);
	//
protected:
	void	GetRenderables(std::vector<IRenderable*>& vecRenderableIn, std::vector<IRenderable*>& vecRenderable, ERENDERTYPEFILTER eFillter);
	virtual	void	SetRenderStageState(ERENDERTYPEFILTER eFillter);
private:
	const RenderPath* m_pRenderPath;
};

