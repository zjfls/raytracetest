#pragma once

struct IntersetData
{
	float fDist;
	Vector3 vecPos;
};

class IntersetResults
{
public:
	IntersetResults();
	virtual ~IntersetResults();

	bool m_bInterset;
	std::vector<IntersetData> m_vecIntersetDatas;
};

