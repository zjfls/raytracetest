#pragma once
#include "H:\github\raytracetest\thirdparty\qtpropertybrowser\src\qttreepropertybrowser.h"


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
};

