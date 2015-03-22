#pragma once
class RenderStage;
class RenderPath
{
public:
	RenderPath(string strName);
	virtual ~RenderPath();
	



	unsigned int	GetStageCount() const;
	RenderStage*	GetStage(unsigned int i) const;
	void			AddStage(RenderStage* stage);



private:
	std::vector<RenderStage*> m_vecStages;
public:
	string m_strName;
};

