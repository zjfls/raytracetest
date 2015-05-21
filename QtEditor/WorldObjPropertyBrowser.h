#pragma once
#include "qttreepropertybrowser.h"
class QtVariantPropertyManager;
class QtVariantEditorFactory;
class QtGroupPropertyManager;
class QtStringPropertyManager;
class IWorldObj;
class WorldObjPropertyBrowser :
	public QtTreePropertyBrowser
{
	Q_OBJECT
public:
	WorldObjPropertyBrowser();
	virtual ~WorldObjPropertyBrowser();



	void	SetTarget(shared_ptr<IWorldObj> pObj);
private:
	shared_ptr<IWorldObj> m_pSelectObj;
	QtVariantPropertyManager* variantManager;// = new QtVariantPropertyManager(this);
	QtVariantEditorFactory*	variantFactory;// = new QtVariantEditorFactory(this);
	QtGroupPropertyManager *groupManager;// = new QtGroupPropertyManager(this);
	QtStringPropertyManager *stringManager;// = new QtStringPropertyManager(w);
};

