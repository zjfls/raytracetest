#pragma once
#include "RenderEnum.h"
#include "DepthBuffer.h"
namespace ZG
{
	class MAIN_API IRenderTarget :public GameObjectBase
	{
	public:
		IRenderTarget();
		virtual ~IRenderTarget();
		virtual bool Resize(int nWidth, int nHeight) = 0;


		unsigned int m_nWidth;
		unsigned int m_nHeight;
		TARGETFORMAT m_eTargetFormt;
		bool bDepth;
		TARGETFORMAT m_eDepthFormt;
		EMULTISAMPLETYPE m_eMultiSampleType;
		unsigned int m_nMultiSampleQuality;

		//for multirendertarget use
		std::map<int, SmartPointer<IRenderTarget>> m_AdditionalTarget;
		SmartPointer<DepthBuffer> m_DepthBuffer;
	};
}


