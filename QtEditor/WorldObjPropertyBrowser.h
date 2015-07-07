#pragma once
#include "qttreepropertybrowser.h"
#include "ModuleBase.h"
class QtVariantPropertyManager;
class QtVariantEditorFactory;
class QtGroupPropertyManager;
class QtStringPropertyManager;
class QtLocalePropertyManager;
class FilePathManager;
class QtDoublePropertyManager;
class QtTexturePropertyManager;

class QtProperty;
class QVariant;

namespace ZG
{
	class IWorldObj;
	class ModuleBase;
	class EditorModuleProperty;
	class WorldObjPropertyBrowser :
		public QtTreePropertyBrowser
	{
		Q_OBJECT
	public:
		WorldObjPropertyBrowser();
		virtual ~WorldObjPropertyBrowser();
		void	UpdateProperty();


		void	SetTarget(SmartPointer<IWorldObj> pObj);
	private:
		void	AddModule(SmartPointer<ModuleBase> pModule);
		private slots:
		void valueChanged(QtProperty *pProp, const QVariant &v);
		void valueChanged(QtProperty *pProp, double);


		void SetDoubleStep(QtProperty* pProperty);
		//virtual void itemChanged(QtBrowserItem *item);
		
		void	AddEditorProperty(SmartPointer<ModuleBase> pModule, std::string propName, QtProperty* pProp);
	private:
		SmartPointer<IWorldObj> m_pSelectObj;
		QtVariantPropertyManager* variantManager;// = new QtVariantPropertyManager(this);
		QtVariantEditorFactory*	variantFactory;// = new QtVariantEditorFactory(this);
		QtGroupPropertyManager *groupManager;// = new QtGroupPropertyManager(this);
		QtStringPropertyManager *stringManager;// = new QtStringPropertyManager(w);
		QtLocalePropertyManager *localeManager;
		QtDoublePropertyManager *doubleManager;
		FilePathManager			*filePathManager;
		QtTexturePropertyManager* texturePropertyManager;

		std::unordered_map<QtProperty*, EditorModuleProperty*> m_PropertyMap;
	};
}


