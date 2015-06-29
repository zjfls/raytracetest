#pragma once
#include "EditorRenderView.h"
#include "IWorldObj.h"
#include "Vector2.h"
namespace ZG
{
	class CameraBase;
	class RasterRender;
	class EDITOR_API EditorSceneView :
		public EditorRenderView
	{
	public:
		EditorSceneView();
		virtual ~EditorSceneView();
		virtual void Update();
		virtual void Resize(unsigned int nWidth, unsigned int nHeight);

		virtual void Create(unsigned int nWidth, unsigned int nHeight, int windowID);
		//
		virtual void OnMouseWheel(short zDelta, Vector2& pt);
		virtual void OnMouseMove(Vector2& pt);
		virtual void OnMouseLButtonDown(Vector2& pt);
		void OnMouseLButtonRelease(Vector2& pt) override;
		virtual void OnMouseRButtonDown(Vector2& pt);
		virtual void OnKeyPressed(int key);
		void	OnClick(Vector2& pt) override;
		//
		void		FocusTarget(IWorldObj* pObj);
		//
		void		UpdateGizmo();
		void		DrawGizmo();
		//
		SmartPointer<IWorldObj> m_pCamera;
		SmartPointer<CameraBase> m_pCameraModule;
		virtual void OnDragEnter(Vector2& pos, std::string file);
		virtual void OnDrop(Vector2& pos, std::string path);
		//
		//virtual void OnClick(Vector2& pos);
	private:
		void	UpdateCamera();
	private:
		Vector2 m_LastMousePos;
	};
}


