#include "stdafx.h"
#include "IntersetResults.h"
bool SortNear(const IntersectData& d1, const IntersectData& d2)
{
	return d1.fDist < d2.fDist;

}
bool SortFar(const IntersectData& d1, const IntersectData& d2)
{
	return d1.fDist < d2.fDist;
}

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

void ZG::IntersectResults::sortNearFirst()
{
	std::sort(std::begin(m_vecIntersetDatas), std::end(m_vecIntersetDatas), SortNear);
}

void ZG::IntersectResults::sortFarFirst()
{
	std::sort(std::begin(m_vecIntersetDatas), std::end(m_vecIntersetDatas), SortFar);
}
