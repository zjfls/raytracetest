#include "stdafx.h"
#include "WorldObjPropertyBrowser.h"
#include "qtpropertybrowser.h"
#include "qtpropertymanager.h"
#include "qtvariantproperty.h"
#include "IWorldObj.h"
#include "ModuleBase.h"
#include "Mesh.h"
#include "Transform.h"
#include "RasterCamera.h"
#include "MathDefine.h"
#include "MeshResource.h"
#include "variantmanager.h"
#include "filepathmanager.h"
#include "FileEditFactory.h"


WorldObjPropertyBrowser::WorldObjPropertyBrowser()
{
	//
	variantManager = new QtVariantPropertyManager(this);
	variantFactory = new QtVariantEditorFactory(this);
	groupManager = new QtGroupPropertyManager(this);
	stringManager = new QtStringPropertyManager(this);
	localeManager = new QtLocalePropertyManager(this);


	setFactoryForManager(variantManager, variantFactory);


	filePathManager = new FilePathManager;
	FileEditFactory* fileEditFactory = new FileEditFactory;
	setFactoryForManager(filePathManager, fileEditFactory);
	SetTarget(nullptr);
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
	if (pObj == nullptr /*|| pObj == m_pSelectObj*/)
	{
		return;
	}
	//
	//
	QList<QtProperty*> pList = properties();
	QListIterator<QtProperty*> it(pList);
	while (it.hasNext())
	{
		QtProperty* item = it.next();
		delete item;
	}
	QtProperty* pName = stringManager->addProperty(tr("Name"));
	stringManager->setValue(pName, QString::fromStdString(pObj->m_strName));
	addProperty(pName);
	//
	//
	for (int i = 0; i < pObj->GetModuleCount(); ++i)
	{
		std::shared_ptr<ModuleBase> pModule = pObj->GetModule(i);
		AddModule(pModule);
	}
}

void WorldObjPropertyBrowser::AddModule(shared_ptr<ModuleBase> pModule)
{
	//
	const type_info& tinfo = typeid(*pModule.get());
	std::string className = tinfo.name();
	if (typeid(*pModule.get()) == typeid(Transform))
	{
		shared_ptr<Transform> pTransform = dynamic_pointer_cast<Transform>(pModule);
		QtProperty* pPropGroup = groupManager->addProperty(tr("Transform"));
		QtProperty* pPropTranslate = groupManager->addProperty(tr("Translate"));
		QtProperty* pPropRotation = groupManager->addProperty(tr("Rotation"));
		QtProperty* pPropScale = groupManager->addProperty(tr("Scale"));
		//Translate
		QtVariantProperty* pProperty;
		pProperty = variantManager->addProperty(QVariant::Double, tr("X"));
		pProperty->setValue(pTransform->GetLocalTranslate().m_fx);
		pPropTranslate->addSubProperty(pProperty);
		//
		pProperty = variantManager->addProperty(QVariant::Double, tr("Y"));
		pProperty->setValue(pTransform->GetLocalTranslate().m_fy);
		pPropTranslate->addSubProperty(pProperty);
		//
		pProperty = variantManager->addProperty(QVariant::Double, tr("Z"));
		pProperty->setValue(pTransform->GetLocalTranslate().m_fz);
		pPropTranslate->addSubProperty(pProperty);
		//
		//Rotation
		pProperty = variantManager->addProperty(QVariant::Double, tr("X"));
		pProperty->setValue(pTransform->GetOrientation().m_vecEulerAngle.m_fx);
		pPropRotation->addSubProperty(pProperty);
		//
		pProperty = variantManager->addProperty(QVariant::Double, tr("Y"));
		pProperty->setValue(pTransform->GetOrientation().m_vecEulerAngle.m_fy);
		pPropRotation->addSubProperty(pProperty);
		//
		pProperty = variantManager->addProperty(QVariant::Double, tr("Z"));
		pProperty->setValue(pTransform->GetOrientation().m_vecEulerAngle.m_fz);
		pPropRotation->addSubProperty(pProperty);
		//
		//scale
		pProperty = variantManager->addProperty(QVariant::Double, tr("X"));
		pProperty->setValue(pTransform->GetScale().m_fx);
		pPropScale->addSubProperty(pProperty);
		//
		pProperty = variantManager->addProperty(QVariant::Double, tr("Y"));
		pProperty->setValue(pTransform->GetScale().m_fy);
		pPropScale->addSubProperty(pProperty);
		//
		pProperty = variantManager->addProperty(QVariant::Double, tr("Z"));
		pProperty->setValue(pTransform->GetScale().m_fz);
		pPropScale->addSubProperty(pProperty);
		//
		pPropGroup->addSubProperty(pPropTranslate);
		pPropGroup->addSubProperty(pPropRotation);
		pPropGroup->addSubProperty(pPropScale);
		addProperty(pPropGroup);
	}
	if (typeid(*pModule.get()) == typeid(Mesh))
	{
		shared_ptr<Mesh> pMesh = dynamic_pointer_cast<Mesh>(pModule);
		QtProperty* pMeshGroup = groupManager->addProperty(tr("Mesh"));
		std::string pMeshRef = "";
		if (pMesh->GetMeshResource() != nullptr)
		{
			pMeshRef = pMesh->GetMeshResource()->GetRefPath();
		}
		QtProperty * pFilePath = filePathManager->addProperty(tr("MeshPath"));
		filePathManager->setValue(pFilePath,pMeshRef.c_str());
		filePathManager->setFilter(pFilePath, "MeshFile files (*.Mesh)");
		pMeshGroup->addSubProperty(pFilePath);
		addProperty(pMeshGroup);
	}
	if (typeid(*pModule.get()) == typeid(RasterCamera))
	{
		shared_ptr<RasterCamera> pCamera = dynamic_pointer_cast<RasterCamera>(pModule);
		QtProperty*	pCameraProperty = groupManager->addProperty(tr("RasterCamera"));
		//
		QtVariantProperty* pProperty = variantManager->addProperty(QVariant::Double, tr("FOV"));
		pProperty->setValue(pCamera->m_fFovy);
		pCameraProperty->addSubProperty(pProperty);
		//
		pProperty = variantManager->addProperty(QVariant::Double, tr("Aspect"));
		pProperty->setValue(pCamera->m_fAspect);
		pCameraProperty->addSubProperty(pProperty);
		//
		pProperty = variantManager->addProperty(QVariant::Double, tr("Near Plane"));
		pProperty->setValue(pCamera->m_fNear);
		pCameraProperty->addSubProperty(pProperty);
		//
		pProperty = variantManager->addProperty(QVariant::Double, tr("Far Plane"));
		pProperty->setValue(pCamera->m_fFar);
		pCameraProperty->addSubProperty(pProperty);
		addProperty(pCameraProperty);
		//
		//float m_fFovy;
		//float m_fAspect;
		//float m_fNear;
		//float m_fFar;
		//shared_ptr<RasterCamera> pCamera = dynamic_pointer_cast<RasterCamera>(pModule);
		//CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("Camera"));
		//CMFCFloatGridProperty* pProp = new CMFCFloatGridProperty(_T("FOV"), (_variant_t)pCamera->m_fFovy, "CAMERAFOV");
		//pGroup->AddSubItem(pProp);
		//pProp = new CMFCFloatGridProperty(_T("Aspect"), (_variant_t)pCamera->m_fAspect, "CAMERAFOV");
		//pGroup->AddSubItem(pProp);
		//pProp = new CMFCFloatGridProperty(_T("Near Plane"), (_variant_t)pCamera->m_fNear, "NEARPLANE");
		//pGroup->AddSubItem(pProp);
		//pProp = new CMFCFloatGridProperty(_T("Far Plane"), (_variant_t)pCamera->m_fFar, "FARPLANE");
		//pGroup->AddSubItem(pProp);
		//m_wndPropList.AddProperty(pGroup);
	}
	//if (typeid(*pModule.get()) == typeid(Transform))
	//{
	//	//
	//	shared_ptr<Transform> pTransform = dynamic_pointer_cast<Transform>(pModule);
	//	//
	//	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("Transform"));
	//	//translate
	//	CMFCPropertyGridProperty* pGroupTranslate = new CMFCPropertyGridProperty(_T("Translate"));
	//	pGroup->AddSubItem(pGroupTranslate);
	//	CMFCFloatGridProperty* pProp = new CMFCFloatGridProperty(_T("x"), (_variant_t)pTransform->GetLocalTranslate().m_fx, "translate_x");
	//	//pProp->EnableSpinControl(TRUE, MINFLOAT, MAXFLOAT);
	//	pGroupTranslate->AddSubItem(pProp);
	//	pProp = new CMFCFloatGridProperty(_T("y"), (_variant_t)pTransform->GetLocalTranslate().m_fy, "translate_y");
	//	pGroupTranslate->AddSubItem(pProp);
	//	pProp = new CMFCFloatGridProperty(_T("z"), (_variant_t)pTransform->GetLocalTranslate().m_fz, "translate_z");
	//	pGroupTranslate->AddSubItem(pProp);


	//	//rotation
	//	CMFCPropertyGridProperty* pGroupRotation = new CMFCPropertyGridProperty(_T("Rotation"));
	//	pGroup->AddSubItem(pGroupRotation);
	//	pProp = new CMFCFloatGridProperty(_T("x"), (_variant_t)pTransform->GetOrientation().m_vecEulerAngle.m_fx, "rotation_x");
	//	//pProp->EnableSpinControl(TRUE, MINFLOAT, MAXFLOAT);
	//	pGroupRotation->AddSubItem(pProp);
	//	pProp = new CMFCFloatGridProperty(_T("y"), (_variant_t)pTransform->GetOrientation().m_vecEulerAngle.m_fy, "rotation_y");
	//	pGroupRotation->AddSubItem(pProp);
	//	pProp = new CMFCFloatGridProperty(_T("z"), (_variant_t)pTransform->GetOrientation().m_vecEulerAngle.m_fz, "rotation_z");
	//	pGroupRotation->AddSubItem(pProp);

	//	//scale
	//	CMFCPropertyGridProperty* pGroupScale = new CMFCPropertyGridProperty(_T("Scale"));
	//	pGroup->AddSubItem(pGroupScale);
	//	pProp = new CMFCFloatGridProperty(_T("x"), (_variant_t)pTransform->GetScale().m_fx, "scale_x");
	//	//pProp->EnableSpinControl(TRUE, MINFLOAT, MAXFLOAT);
	//	pGroupScale->AddSubItem(pProp);
	//	pProp = new CMFCFloatGridProperty(_T("y"), (_variant_t)pTransform->GetScale().m_fy, "scale_y");
	//	pGroupScale->AddSubItem(pProp);
	//	pProp = new CMFCFloatGridProperty(_T("z"), (_variant_t)pTransform->GetScale().m_fz, "scale_z");
	//	pGroupScale->AddSubItem(pProp);

	//	//pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("项 1"), (_variant_t)_T("值 1"), _T("此为说明")));
	//	//pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("项 2"), (_variant_t)_T("值 2"), _T("此为说明")));
	//	//pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("项 3"), (_variant_t)_T("值 3"), _T("此为说明")));
	//	m_wndPropList.AddProperty(pGroup);
	//}
	//if (typeid(*pModule.get()) == typeid(Mesh))
	//{
	//	shared_ptr<Mesh> pMesh = dynamic_pointer_cast<Mesh>(pModule);
	//	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("Mesh"));
	//	std::string pMeshRef = "";
	//	if (pMesh->GetMeshResource() != nullptr)
	//	{
	//		pMeshRef = pMesh->GetMeshResource()->GetRefPath();
	//	}
	//	CMFCPropertyGridFileProperty* pFile = new CMFCPropertyGridFileProperty("MeshFile", pMeshRef.c_str());
	//	pGroup->AddSubItem(pFile);


	//	m_wndPropList.AddProperty(pGroup);
	//}
	//if (typeid(*pModule.get()) == typeid(RasterCamera))
	//{
	//	//float m_fFovy;
	//	//float m_fAspect;
	//	//float m_fNear;
	//	//float m_fFar;
	//	shared_ptr<RasterCamera> pCamera = dynamic_pointer_cast<RasterCamera>(pModule);
	//	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("Camera"));
	//	CMFCFloatGridProperty* pProp = new CMFCFloatGridProperty(_T("FOV"), (_variant_t)pCamera->m_fFovy, "CAMERAFOV");
	//	pGroup->AddSubItem(pProp);
	//	pProp = new CMFCFloatGridProperty(_T("Aspect"), (_variant_t)pCamera->m_fAspect, "CAMERAFOV");
	//	pGroup->AddSubItem(pProp);
	//	pProp = new CMFCFloatGridProperty(_T("Near Plane"), (_variant_t)pCamera->m_fNear, "NEARPLANE");
	//	pGroup->AddSubItem(pProp);
	//	pProp = new CMFCFloatGridProperty(_T("Far Plane"), (_variant_t)pCamera->m_fFar, "FARPLANE");
	//	pGroup->AddSubItem(pProp);
	//	m_wndPropList.AddProperty(pGroup);
	//}
}
