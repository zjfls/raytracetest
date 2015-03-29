#pragma once
#include "RenderEnum.h"
class CameraBase;
class IWorld;
class IRenderTarget;
class RenderView;
class CameraBase;
class IRenderable;
struct stRenderViewInfo;
class MAIN_API IRender
{
public:
	IRender();
	virtual ~IRender();


	/*

	*Summary: render a world

	*Parameters:

	*   pCammera:the camera render to use
	*	pWorld:the world to be render

	*Return : int if success return 0

	*/
	virtual int Render(CameraBase* pCammera, IWorld* pWorld) = 0;
	/*

	*Summary: render a renderable

	*Parameters:

	*   pRenderable:the target to be rendered

	*Return : void

	*/
	virtual void Render(IRenderable* pRenderable){};
	//
	void	SetRenderTarget(IRenderTarget* pTarget);
	//
	IRenderTarget*	CreateRenderTarget(unsigned int width, unsigned int height, TARGETFORMAT eTargetFormat, bool bDepth = false, TARGETFORMAT eDepthFormat = TFNONE, EMULTISAMPLETYPE = MSNONE, unsigned int nMultiSampleQuality = 0);
	//
	RenderView*	CreateRenderView(const stRenderViewInfo& renderView);



private:
	void SetCurrentRenderCamera(CameraBase* pCamera);

protected:
	CameraBase* m_pCurrentRenderCamera;
	friend class CameraBase;
	friend class RenderState;
	friend class RenderPass;
	friend class CameraRenderer;
};

