#pragma once
#include "RenderEnum.h"
//#include "RenderTargetGroup.h"
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
	virtual int Render(SmartPointer<CameraBase> pCammera, SmartPointer<IWorld> pWorld,IRenderTarget* pTarget) = 0;
	/*

	*Summary: render a renderable

	*Parameters:

	*   pRenderable:the target to be rendered

	*Return : void

	*/
	virtual void Render(SmartPointer<IRenderable> pRenderable){};
	//
	virtual void	SetRenderTarget(int nIndex,IRenderTarget* pTarget);
	//
	IRenderTarget*	CreateRenderTarget(unsigned int width, unsigned int height, TARGETFORMAT eTargetFormat, bool bDepth = false, TARGETFORMAT eDepthFormat = TFNONE, EMULTISAMPLETYPE = MSNONE, unsigned int nMultiSampleQuality = 0);
	//
	RenderView*	CreateRenderView(const stRenderViewInfo& renderView);



private:
	void SetCurrentRenderCamera(SmartPointer<CameraBase> pCamera);

protected:
	SmartPointer<CameraBase> m_pCurrentRenderCamera;

	friend class CameraBase;
	friend class RenderState;
	friend class RenderPass;
	friend class CameraRenderer;
};

