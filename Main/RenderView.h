#pragma once
#include "IRenderTarget.h"


struct MAIN_API stRenderViewInfo
{
	stRenderViewInfo();

	//for target
	unsigned int m_nWidth;
	unsigned int m_nHeight;
	TARGETFORMAT m_eTargetFormt;
	bool m_bDepth;
	TARGETFORMAT m_eDepthFormt;
	EMULTISAMPLETYPE m_eMultiSampleType;
	unsigned int m_nMultiSampleQuality;
	//for view
	EBUFFSWARP	m_eSwapEffect;
	unsigned int m_nBackBufferCount;
	int m_windowID;
	bool m_bWindowed;
	int	m_nPresentFlag;
	unsigned int m_nRefreshHZ;
	unsigned int m_nPresentInterval;
};
class MAIN_API RenderView :
	public IRenderTarget
{
public:
	RenderView();
	~RenderView();


	virtual bool Resize(int nX,int nY) = 0;

	virtual bool Present() = 0;
	//
	unsigned int m_nBackBufferCount;
	int m_windowID;
	bool bWindowed;
	bool bDepth;
	TARGETFORMAT m_eDepthFormt;
	int	m_nPresentFlag;
	unsigned int m_nRefreshHZ;
	unsigned int m_nPresentInterval;
};

