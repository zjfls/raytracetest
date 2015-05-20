#include "stdafx.h"
#include "WorldObjPropertyBrowser.h"
#include "qtpropertybrowser.h"
#include "qtpropertymanager.h"
#include "qtvariantproperty.h"



WorldObjPropertyBrowser::WorldObjPropertyBrowser()
{
	//
	variantManager = new QtVariantPropertyManager(this);
	variantFactory = new QtVariantEditorFactory(this);
	groupManager = new QtGroupPropertyManager(this);



	setFactoryForManager(variantManager, variantFactory);


	m_pSelectObj = nullptr;
	////
	//QtProperty* pTransform = groupManager->addProperty("WorldObj");
	//QtVariantProperty* pProperty;
	//pProperty = variantManager->addProperty(QVariant::Double, tr("Position X"));
	//pProperty->setValue(11213.0f);
	//pTransform->addSubProperty(pProperty);
	//QtBrowserItem* pItem = addProperty(pTransform);
}


WorldObjPropertyBrowser::~WorldObjPropertyBrowser()
{
}

void WorldObjPropertyBrowser::SetTarget(shared_ptr<IWorldObj> pObj)
{
	if (pObj == nullptr || pObj == m_pSelectObj)
	{
		return;
	}
	//
	//
	removeProperty()
}
