#pragma once
namespace ZG
{
	class RenderView;
	class Vector2;
	class EDITOR_API EditorRenderView
	{
	public:
		EditorRenderView();
		virtual ~EditorRenderView();

		virtual void Create(unsigned int nWidth, unsigned int nHeight, int windowID);
		virtual void Resize(unsigned int nWidth, unsigned int nHeight);
		virtual void OnMouseWheel(short zDelta, Vector2& pt);
		virtual void OnMouseMove(Vector2& pt);
		virtual void OnMouseLButtonDown(Vector2& pt);
		virtual void OnMouseLButtonRelease(Vector2& pt);
		virtual void OnMouseRButtonDown(Vector2& pt);
		virtual void OnMouseRButtonRelease(Vector2& pt);
		virtual void OnMouseMButtonDown(Vector2& pt);
		virtual void OnMouseMButtonRelease(Vector2& pt);
		virtual void OnKeyPressed(int key);
		virtual void OnClick(Vector2& pos) = 0;

		virtual void OnDragEnter(Vector2& pos, std::string path){};
		virtual void OnDrop(Vector2& pos, std::string path){};
		//
		virtual void Update();
		//
		//virtual void OnClick(Vector2& pos){};
		//
		RenderView* m_pRenderView;
		//
		bool m_bIsFocus;
		//
		bool m_bShow;
		//

	};
}
