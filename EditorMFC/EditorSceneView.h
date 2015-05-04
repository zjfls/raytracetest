#pragma once
#include "EditorRenderView.h"
#include "IWorldObj.h"
class EditorSceneView :
	public EditorRenderView
{
public:
	EditorSceneView();
	virtual ~EditorSceneView();
	virtual void Update();
	virtual void Resize(unsigned int nWidth, unsigned int nHeight);


	//
	virtual void OnMouseWheel(short zDelta, Vector2& pt);
	virtual void OnMouseMove(Vector2& pt);
	virtual void OnMouseLButtonDown(Vector2& pt);
	//
	std::shared_ptr<IWorldObj> m_pCamera;
};

