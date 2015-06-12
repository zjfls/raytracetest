#include "stdafx.h"
#include "IntersetResults.h"


IntersectResults::IntersectResults()
{
	m_bInterset = false;
}


IntersectResults::~IntersectResults()
{

}

void ZG::IntersectResults::appendResult(IntersectResults& r)
{
	for each (IntersectData data in r.m_vecIntersetDatas)
	{
		m_vecIntersetDatas.push_back(data);
	}
}
