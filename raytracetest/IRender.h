#pragma once
#include "RenderEnum.h"
class CameraBase;
class IWorld;
class IRenderTarget;
class RenderView;
struct stRenderViewInfo;
class IRender
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
	IRenderTarget*	CreateRenderTarget(unsigned int width, unsigned int height, TARGETFORMAT eTargetFormat, bool bDepth = false, TARGETFORMAT eDepthFormat = TFNONE, EMULTISAMPLETYPE = MSNONE,unsigned int nMultiSampleQuality = 0);
	//
	RenderView*	CreateRenderView(const stRenderViewInfo& renderView);
};

