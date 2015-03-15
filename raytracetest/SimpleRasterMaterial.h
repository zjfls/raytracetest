#pragma once
#include "RasterMaterial.h"



class MaterialProp
{
public:
	MaterialProp();
	virtual ~MaterialProp();

	enum EMATPROPTYPE
	{
		eMatPTypeFloat,
		eMatPTypeFloat1,
		eMatPTypeFloat2,
		eMatPTypeFloat3,
		eMatPTypeFloat4,
		eMatPTypeMat33,
		eMatPTypeMat44,
		eMatPTypeSampler
	};
};

class SimpleRasterMaterial :
	public RasterMaterial
{
public:
	SimpleRasterMaterial();
	virtual ~SimpleRasterMaterial();
};

