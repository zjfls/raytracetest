#pragma once
#include "EditorRenderView.h"
#include "IWorldObj.h"
#include "Vector2.h"
class EDITOR_API EditorSceneView :
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
	virtual void OnMouseRButtonDown(Vector2& pt);
	virtual void OnKeyPressed(int key);
	//
	std::shared_ptr<IWorldObj> m_pCamera;


private:
	Vector2 m_LastMousePos;
};

