#pragma once
#include "RenderEnum.h"
class RenderStage
{
public:
	RenderStage(string name, ERENDERTYPEFILTER eFillter);
	virtual ~RenderStage();


	string m_strName;
	ERENDERTYPEFILTER m_eFillter;
};

