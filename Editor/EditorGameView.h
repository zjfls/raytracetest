#pragma once
#include "EditorRenderView.h"
namespace ZG
{
	class EDITOR_API EditorGameView :
		public EditorRenderView
	{
	public:
		EditorGameView();
		virtual ~EditorGameView();
	};

}