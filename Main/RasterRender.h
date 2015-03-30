#pragma once
#include "IRender.h"
#include "RenderStage.h"
class RenderPath;
class IRenderable;
class RenderSystem;
class HardwareVertexShader;
class HardwareFragShader;
class HardwareIndexBuffer;
class HardwareVertexBuffer;
class HardwareTexture;
class RasterCamera;
class RenderStateCollection;
class MAIN_API RasterRender :
	public IRender
{
public:
	/*RasterRender();*/
	RasterRender(const RenderPath* pPath);
	virtual ~RasterRender();
	//render a obj
	virtual void Render(IRenderable* pRender);


	//
	
	//
	virtual int Render(std::vector<IRenderable*>& pRenderableList);
	//
	virtual int Render(CameraBase* pCammera, IWorld* pWorld);



	//
	virtual void UpdateProjCamera(CameraBase* pCamera) = 0;
	virtual void Render(HardwareIndexBuffer* pIndexBuff, HardwareVertexBuffer* pVertexBuff) = 0;
	virtual bool SetVertexShader(HardwareVertexShader* pVertexShader) = 0;
	virtual bool SetFragShader(HardwareFragShader* pFragShader) = 0;
	virtual bool SetTexture(int nSamplerID, HardwareTexture* pTexture) = 0;
	virtual bool SetRenderStateCollection(const RenderStateCollection& stateCollection) = 0;
	virtual bool SetBlendEnable(bool b) = 0;
	virtual bool SetBlendSrc(EALPHABLEND eBlend) = 0;
	virtual bool SetBlendDst(EALPHABLEND eBlend) = 0;
	virtual bool SetZTestEnable(bool b) = 0;
	virtual bool SetZWriteEnable(bool b) = 0;
	virtual bool SetZFunc(ERENDERCMPFUNC eCmp) = 0;
	virtual bool SetAlphaTest(bool b) = 0;
	virtual bool SetAlphaFunc(ERENDERCMPFUNC eCmp) = 0;
	virtual bool SetAlphaTestFactor(float f) = 0;
	virtual bool SetCullMode(ERENDERCULL eCull) = 0;
	//
protected:
	void	GetRenderables(std::vector<IRenderable*>& vecRenderableIn, std::vector<IRenderable*>& vecRenderable, ERENDERTYPEFILTER eFillter);
	//virtual	void	SetRenderStageState(ERENDERTYPEFILTER eFillter);
protected:
	const RenderPath* m_pRenderPath;
	RenderSystem* m_pRenderSystem;

	friend class RenderPass;
	//friend class RenderStage;
	friend class RenderSystem;
	friend class CameraRenderer;
	//RasterCamera* m_pRenderCamera;
};

