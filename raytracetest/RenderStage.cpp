#include "stdafx.h"
#include "RenderStage.h"


RenderStage::RenderStage(string strName, ERENDERTYPEFILTER eFillter)
	:m_strName(strName)
	, m_eFillter(eFillter)
{
}


RenderStage::~RenderStage()
{
}
