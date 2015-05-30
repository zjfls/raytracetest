#pragma once
#include "VertexData.h"
#include "Vector3.h"
#include "Vector2.h"
class FOUNDATION_API DynamicVertexData :
	public VertexData
{
public:
	DynamicVertexData();
	virtual ~DynamicVertexData();
	virtual void getBoundingMaxAndMin(Vector3& min, Vector3 max);
	std::vector<Vector3> m_PositionData;
	std::vector<Vector2> m_UVData;
	std::vector<Vector3> m_NormalData;
};

