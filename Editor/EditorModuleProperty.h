#pragma once

namespace ZG
{
	class ModuleBase;
	class EDITOR_API EditorModuleProperty
	{
	public:
		EditorModuleProperty();
		virtual ~EditorModuleProperty();
		SmartPointer<ModuleBase> m_pModule;
		std::string m_PropName;


		virtual void SetProperty(void* pData);
		void		GetValue(void* pData);
	};
}


