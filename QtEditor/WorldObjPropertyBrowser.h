#pragma once
#include "qttreepropertybrowser.h"
class QtVariantPropertyManager;
class QtVariantEditorFactory;
class QtGroupPropertyManager;
class QtStringPropertyManager;
class QtLocalePropertyManager;
class FilePathManager;
class IWorldObj;
class ModuleBase;
class QtProperty;
class QVariant;
class EditorModuleProperty;
class WorldObjPropertyBrowser :
	public QtTreePropertyBrowser
{
	Q_OBJECT
public:
	WorldObjPropertyBrowser();
	virtual ~WorldObjPropertyBrowser();



	void	SetTarget(shared_ptr<IWorldObj> pObj);
private:
	void	AddModule(shared_ptr<ModuleBase> pModule);
	private slots:
	void valueChanged(QtProperty *pProp, const QVariant &v);


	void	AddEditorProperty(shared_ptr<ModuleBase> pModule, std::string propName,QtProperty* pProp);
private:
	shared_ptr<IWorldObj> m_pSelectObj;
	QtVariantPropertyManager* variantManager;// = new QtVariantPropertyManager(this);
	QtVariantEditorFactory*	variantFactory;// = new QtVariantEditorFactory(this);
	QtGroupPropertyManager *groupManager;// = new QtGroupPropertyManager(this);
	QtStringPropertyManager *stringManager;// = new QtStringPropertyManager(w);
	QtLocalePropertyManager *localeManager;
	FilePathManager			*filePathManager;

	std::unordered_map<QtProperty*, EditorModuleProperty*> m_PropertyMap;
};

