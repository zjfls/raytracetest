#pragma once



class IRenderable;
struct IntersetData
{
	float fDist;
	Vector3 vecPos;
	Vector3 vecNormal;
	bool bBackface;
	IRenderable *pRender;
};

class IntersetResults
{
public:
	IntersetResults();
	virtual ~IntersetResults();

	bool m_bInterset;
	std::vector<IntersetData> m_vecIntersetDatas;
};

