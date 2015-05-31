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
#include "PointLight.h"
#include "DirectionalLight.h"
#include "EditorModuleProperty.h"
#include <unordered_map>
#include "Sphere3D.h"

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



	connect(variantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
		this, SLOT(valueChanged(QtProperty *, const QVariant &)));
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
	for each (std::pair<QtProperty*, EditorModuleProperty*> p in m_PropertyMap)
	{
		delete p.second;
	}
	m_PropertyMap.clear();
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
		AddEditorProperty(pTransform, "TRANSLATEX", pProperty);
		//
		pProperty = variantManager->addProperty(QVariant::Double, tr("Y"));
		pProperty->setValue(pTransform->GetLocalTranslate().m_fy);
		pPropTranslate->addSubProperty(pProperty);
		AddEditorProperty(pTransform, "TRANSLATEY", pProperty);
		//
		pProperty = variantManager->addProperty(QVariant::Double, tr("Z"));
		pProperty->setValue(pTransform->GetLocalTranslate().m_fz);
		pPropTranslate->addSubProperty(pProperty);
		AddEditorProperty(pTransform, "TRANSLATEZ", pProperty);
		//
		//Rotation
		pProperty = variantManager->addProperty(QVariant::Double, tr("X"));
		pProperty->setValue(pTransform->GetOrientation().m_vecEulerAngle.m_fx);
		pPropRotation->addSubProperty(pProperty);
		AddEditorProperty(pTransform, "ROTATIONX", pProperty);
		//
		pProperty = variantManager->addProperty(QVariant::Double, tr("Y"));
		pProperty->setValue(pTransform->GetOrientation().m_vecEulerAngle.m_fy);
		pPropRotation->addSubProperty(pProperty);
		AddEditorProperty(pTransform, "ROTATIONY", pProperty);
		//
		pProperty = variantManager->addProperty(QVariant::Double, tr("Z"));
		pProperty->setValue(pTransform->GetOrientation().m_vecEulerAngle.m_fz);
		pPropRotation->addSubProperty(pProperty);
		AddEditorProperty(pTransform, "ROTATIONZ", pProperty);
		//
		//scale
		pProperty = variantManager->addProperty(QVariant::Double, tr("X"));
		pProperty->setValue(pTransform->GetScale().m_fx);
		pPropScale->addSubProperty(pProperty);
		AddEditorProperty(pTransform, "SCALEX", pProperty);
		//
		pProperty = variantManager->addProperty(QVariant::Double, tr("Y"));
		pProperty->setValue(pTransform->GetScale().m_fy);
		pPropScale->addSubProperty(pProperty);
		AddEditorProperty(pTransform, "SCALEY", pProperty);
		//
		pProperty = variantManager->addProperty(QVariant::Double, tr("Z"));
		pProperty->setValue(pTransform->GetScale().m_fz);
		pPropScale->addSubProperty(pProperty);
		AddEditorProperty(pTransform, "SCALEZ", pProperty);
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
	}
	if (typeid(*pModule.get()) == typeid(PointLight))
	{
		//LightBase
		//GameColor	m_Color;
		//float	m_fIntensity;
		//float	m_bCastShadow;
		//PointLight
		//float m_fRange;
		//float m_fAttenConst;
		//float m_fAttenLinear;
		//float m_fAttenExp;
		shared_ptr<PointLight> pPointLight = dynamic_pointer_cast<PointLight>(pModule);
		QtProperty* pPTGroup = groupManager->addProperty(tr("PointLight"));
		//
		QtVariantProperty* pProperty = variantManager->addProperty(QVariant::Color, tr("LightColor"));
		QColor c;
		/*c.alpha = pPointLight->m_Color.m_fA;*/
		c.setAlphaF(pPointLight->m_Color.m_fA);
		c.setRedF(pPointLight->m_Color.m_fR);
		c.setGreenF(pPointLight->m_Color.m_fG);
		c.setBlueF(pPointLight->m_Color.m_fB);
		pProperty->setValue(c);
		pPTGroup->addSubProperty(pProperty);
		addProperty(pPTGroup);
	}
	if (typeid(*pModule.get()) == typeid(DirectionalLight))
	{
		//LightBase
		//GameColor	m_Color;
		//float	m_fIntensity;
		//float	m_bCastShadow;
		shared_ptr<DirectionalLight> pDirLight = dynamic_pointer_cast<DirectionalLight>(pModule);
		QtProperty* pPTGroup = groupManager->addProperty(tr("DirectioLight"));
		//
		QtVariantProperty* pProperty = variantManager->addProperty(QVariant::Color, tr("LightColor"));
		QColor c;
		/*c.alpha = pPointLight->m_Color.m_fA;*/
		c.setAlphaF(pDirLight->m_Color.m_fA);
		c.setRedF(pDirLight->m_Color.m_fR);
		c.setGreenF(pDirLight->m_Color.m_fG);
		c.setBlueF(pDirLight->m_Color.m_fB);
		pProperty->setValue(c);
		pPTGroup->addSubProperty(pProperty);
		addProperty(pPTGroup);
	}
	if (typeid(*pModule.get()) == typeid(Sphere3D))
	{
		shared_ptr<Sphere3D> pSphere = dynamic_pointer_cast<Sphere3D>(pModule);
		QtProperty* pSphereGroup = groupManager->addProperty(tr("Sphere"));
		addProperty(pSphereGroup);

		QtVariantProperty* pProperty = variantManager->addProperty(QVariant::Double, tr("Radius"));
		pSphereGroup->addSubProperty(pProperty);
		pProperty->setValue(pSphere->m_fRadius);
		AddEditorProperty(pSphere, "RADIUS", pProperty);

		pProperty = variantManager->addProperty(QVariant::Int, tr("Subdivide"));
		pSphereGroup->addSubProperty(pProperty);
		pProperty->setValue(pSphere->m_nSubdivide);
		AddEditorProperty(pSphere, "SUBDIVIDE", pProperty);
	}
}

void WorldObjPropertyBrowser::valueChanged(QtProperty *pProp, const QVariant &v)
{
	if (m_PropertyMap.find(pProp) == std::end(m_PropertyMap))
	{
		return;
	}
	//std::cout << "value changed" << std::endl;

	switch (v.type())
	{
		case QVariant::Double:
		{
			float fValue = v.toDouble();
			m_PropertyMap[pProp]->SetProperty(&fValue);

		}
		break;
		case QVariant::Int:
		{
			int nValue = v.toInt();
			m_PropertyMap[pProp]->SetProperty(&nValue);
		}
		break;
		default:
		{
		}
		break;
	}
}

void WorldObjPropertyBrowser::AddEditorProperty(shared_ptr<ModuleBase> pModule, std::string propName, QtProperty* pProp)
{
	if (m_PropertyMap.find(pProp) != std::end(m_PropertyMap))
	{
		return;
	}
	EditorModuleProperty* pEditorProp = new EditorModuleProperty;
	pEditorProp->m_pModule = pModule;
	pEditorProp->m_PropName = propName;
	m_PropertyMap[pProp] = pEditorProp;
}
