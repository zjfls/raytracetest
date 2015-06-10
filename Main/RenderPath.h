#pragma once
#include "RenderTargetGroup.h"
namespace ZG
{
	class RenderStage;
	class RenderPath
	{
	public:
		RenderPath(string strName);
		virtual ~RenderPath();




		unsigned int	GetStageCount() const;
		RenderStage*	GetStage(unsigned int i) const;
		void			AddStage(RenderStage* stage);


		//virtual void	InitTargetBuffer();
	private:
		std::vector<RenderStage*> m_vecStages;
	public:
		string	m_strName;
		bool	m_bGetPerObjLightInfo;


		RenderTargetGroup m_RenderTargetGroup;
	};

}