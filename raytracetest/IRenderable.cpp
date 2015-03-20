#include "stdafx.h"
#include "IRenderable.h"


IRenderable::IRenderable()
	:m_pVertexData(nullptr)
	, m_pIndexData(nullptr)
	, m_pMaterial(nullptr)
{
	
}


IRenderable::~IRenderable()
{
}

void IRenderable::Update()
{

}
