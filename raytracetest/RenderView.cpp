#include "stdafx.h"
#include "RenderView.h"


RenderView::RenderView()
{
	
}


RenderView::~RenderView()
{
}

stRenderViewInfo::stRenderViewInfo()
{
	m_nWidth = 1024;
	m_nHeight = 768;
	m_eTargetFormt = TFA8R8G8B8;
	m_bDepth = true;
	m_eDepthFormt = TFD24X8;
	m_eMultiSampleType = MSNONE;
	m_nMultiSampleQuality = 0;
	m_eSwapEffect = BSDISCARD;
	m_nBackBufferCount = 2;
	m_windowID = 0;
	m_bWindowed = true;
	m_nPresentFlag = 0;
	m_nRefreshHZ = 60;
	m_nPresentInterval = 1;
}
