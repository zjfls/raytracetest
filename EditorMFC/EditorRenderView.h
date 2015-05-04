#pragma once

class RenderView;
class Vector2;
class EditorRenderView
{
public:
	EditorRenderView();
	virtual ~EditorRenderView();

	void Create(unsigned int nWidth, unsigned int nHeight, int windowID);
	virtual void Resize(unsigned int nWidth, unsigned int nHeight);
	virtual void OnMouseWheel(short zDelta, Vector2& pt);
	virtual void OnMouseMove(Vector2& pt);
	virtual void OnMouseLButtonDown(Vector2& pt);
	//
	virtual void Update() = 0;
	//
	RenderView* m_pRenderView;
};

