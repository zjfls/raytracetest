#pragma once
#include "IRender.h"
#include "RenderStage.h"
class RenderPath;
class IRenderable;
class RenderSystem;
class HardwareVertexShader;
class HardwareFragShader;
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


	virtual bool SetVertexShader(HardwareVertexShader* pVertexShader) = 0;
	virtual bool SetFragShader(HardwareFragShader* pFragShader) = 0;

	//
protected:
	void	GetRenderables(std::vector<IRenderable*>& vecRenderableIn, std::vector<IRenderable*>& vecRenderable, ERENDERTYPEFILTER eFillter);
	//virtual	void	SetRenderStageState(ERENDERTYPEFILTER eFillter);
private:
	const RenderPath* m_pRenderPath;
	RenderSystem* m_pRenderSystem;

	friend class RenderPass;
	//friend class RenderStage;
	friend class RenderSystem;
};

