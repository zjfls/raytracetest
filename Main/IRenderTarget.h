#pragma once
#include "RenderEnum.h"
class MAIN_API IRenderTarget
{
public:
	IRenderTarget();
	virtual ~IRenderTarget();



	unsigned int m_nWidth;
	unsigned int m_nHeight;
	TARGETFORMAT m_eTargetFormt;
	bool bDepth;
	TARGETFORMAT m_eDepthFormt;
	EMULTISAMPLETYPE m_eMultiSampleType;
	unsigned int m_nMultiSampleQuality;
};

