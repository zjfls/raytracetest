#pragma once


namespace ZG
{
	class IRenderable;
	struct IntersectData
	{
		float fDist;
		Vector3 vecPos;
		Vector3 vecNormal;
		bool bBackface;
		IRenderable *pRender;
		int polyIndex;
	};

	class MAIN_API IntersectResults
	{
	public:
		IntersectResults();
		virtual ~IntersectResults();

		bool m_bInterset;
		std::vector<IntersectData> m_vecIntersetDatas;
	};
}
