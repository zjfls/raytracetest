#pragma once
#include "RenderEnum.h"
class RenderStateCollection;
class IRenderable;
enum STAGEMASKTYPE
{
	SMT_IGNORESETSTATE,
	SMT_IGNOREDRAW
};
struct stMaskData
{
	stMaskData()
	{
		m_Type = SMT_IGNORESETSTATE;
		m_pData = nullptr;
	}
	STAGEMASKTYPE m_Type;
	void*	m_pData;
};

class RenderStateMask
{
public:
	RenderStateMask(){};
	virtual ~RenderStateMask(){};
	void Clear()
	{
		m_mapMask.clear();
	}
	void AddMask(RENDERSTATEMASK eMask, bool b)
	{
		m_mapMask[eMask] = stMaskData();
	}
	bool hasMask(RENDERSTATEMASK eMask) const
	{
		if (m_mapMask.find(eMask) != std::end(m_mapMask))
		{
			return true;
		}
		return false;
	}
private:
	std::unordered_map<RENDERSTATEMASK, stMaskData> m_mapMask;
};
class RasterRender;
class RenderStage
{
public:
	RenderStage(string name, ERENDERTYPEFILTER eFillter, ERENDERSTAGEMETHOD eMethod);
	virtual ~RenderStage();




	void	Render(RasterRender* pRender,std::vector<IRenderable*>& vecRenderabls);
	void	SetStageRenderState(RasterRender* pRender);
	string m_strName;
	ERENDERTYPEFILTER m_eFillter;
	ERENDERSTAGEMETHOD m_eMethod;
private:
	void	RenderDepthAndRadiance(RasterRender* pRender,std::vector<IRenderable*>& vecRenderabls);
	void	SetMaterialParam();

	/*

	*Summary: set RenderStates in Collection

	*Parameters:

	*     pRender:the render to be use
	*	  mapStates:the State to be set	

	*Return : int:0 success;1 next draw operation will be ignore

	*/
	int	SetRenderStateCollection(RasterRender* pRender, const RenderStateCollection& mapStates);
	RenderStateMask m_RenderStateMask;
};

