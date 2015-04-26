#pragma once

class RenderView;
class EditorRenderView
{
public:
	EditorRenderView();
	virtual ~EditorRenderView();

	void Create(unsigned int nWidth, unsigned int nHeight, int windowID);
	void Resize(unsigned int nWidth, unsigned int nHeight);

	RenderView* m_pRenderView;
};

