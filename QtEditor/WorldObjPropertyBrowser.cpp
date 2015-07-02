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
#include "skeleton.h"
#include "SkeletonResource.h"
#include "ModuleBase.h"
#include "qteditorfactory.h"

WorldObjPropertyBrowser::WorldObjPropertyBrowser()
{
	//
	variantManager = new QtVariantPropertyManager(this);
	variantFactory = new QtVariantEditorFactory(this);
	groupManager = new QtGroupPropertyManager(this);
	stringManager = new QtStringPropertyManager(this);
	localeManager = new QtLocalePropertyManager(this);
	doubleManager = new QtDoublePropertyManager(this);
	QtDoubleSpinBoxFactory* pDoubleFactory = new QtDoubleSpinBoxFactory;
	setFactoryForManager(doubleManager, pDoubleFactory);
	connect(doubleManager, SIGNAL(valueChanged(QtProperty *, double)),
		this, SLOT(valueChanged(QtProperty *, double)));

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

void WorldObjPropertyBrowser::SetTarget(SmartPointer<IWorldObj> pObj)
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
	std::string strName = typeid(*pObj.get()).name();
	strName = strName.c_str() + 6;

	stringManager->setValue(pName, QString::fromStdString(strName));
	addProperty(pName);
	//
	//
	for (int i = 0; i < pObj->GetModuleCount(); ++i)
	{
		SmartPointer<ModuleBase> pModule = pObj->GetModule(i);
		AddModule(pModule);
	}
}

void WorldObjPropertyBrowser::AddModule(SmartPointer<ModuleBase> pModule)
{
	
	//
	const type_info& tinfo = typeid(*pModule.get());
	std::string className = tinfo.name();
	if (typeid(*pModule.get()) == typeid(Transform))
	{
		SmartPointer<Transform> pTransform = pModule.SmartPointerCast<Transform>();
		QtProperty* pPropGroup = groupManager->addProperty(tr("Transform"));
		QtProperty* pPropTranslate = groupManager->addProperty(tr("Translate"));
		QtProperty* pPropRotation = groupManager->addProperty(tr("Rotation"));
		QtProperty* pPropScale = groupManager->addProperty(tr("Scale"));
		//Translate
		QtProperty* pProperty;
		pProperty = doubleManager->addProperty(tr("X"));
		QtAbstractPropertyManager* pManager = pProperty->propertyManager();
		doubleManager->setValue(pProperty, pTransform->GetLocalTranslate().m_fx);
		pPropTranslate->addSubProperty(pProperty);
		AddEditorProperty(pTransform.get(), "TRANSLATEX", pProperty);
		//
		pProperty = doubleManager->addProperty(tr("Y"));
		doubleManager->setValue(pProperty, pTransform->GetLocalTranslate().m_fy);
		pPropTranslate->addSubProperty(pProperty);
		AddEditorProperty(pTransform.get(), "TRANSLATEY", pProperty);
		//
		pProperty = doubleManager->addProperty(tr("Z"));
		doubleManager->setValue(pProperty, pTransform->GetLocalTranslate().m_fz);
		pPropTranslate->addSubProperty(pProperty);
		AddEditorProperty(pTransform.get(), "TRANSLATEZ", pProperty);
		//
		//Rotation
		pProperty = doubleManager->addProperty(tr("X"));
		doubleManager->setValue(pProperty, pTransform->GetRotation().m_fx);
		pPropRotation->addSubProperty(pProperty);
		AddEditorProperty(pTransform.get(), "ROTATIONX", pProperty);
		//
		pProperty = doubleManager->addProperty(tr("Y"));
		doubleManager->setValue(pProperty, pTransform->GetRotation().m_fy);
		pPropRotation->addSubProperty(pProperty);
		AddEditorProperty(pTransform.get(), "ROTATIONY", pProperty);
		//
		pProperty = doubleManager->addProperty(tr("Z"));
		doubleManager->setValue(pProperty, pTransform->GetRotation().m_fz);
		pPropRotation->addSubProperty(pProperty);
		AddEditorProperty(pTransform.get(), "ROTATIONZ", pProperty);
		//
		//scale
		pProperty = doubleManager->addProperty(tr("X"));
		doubleManager->setValue(pProperty, pTransform->GetScale().m_fx);
		pPropScale->addSubProperty(pProperty);
		AddEditorProperty(pTransform.get(), "SCALEX", pProperty);
		//
		pProperty = doubleManager->addProperty(tr("Y"));
		doubleManager->setValue(pProperty, pTransform->GetScale().m_fy);
		pPropScale->addSubProperty(pProperty);
		AddEditorProperty(pTransform.get(), "SCALEY", pProperty);
		//
		pProperty = doubleManager->addProperty(tr("Z"));
		doubleManager->setValue(pProperty, pTransform->GetScale().m_fz);
		pPropScale->addSubProperty(pProperty);
		AddEditorProperty(pTransform.get(), "SCALEZ", pProperty);
		//
		pPropGroup->addSubProperty(pPropTranslate);
		pPropGroup->addSubProperty(pPropRotation);
		pPropGroup->addSubProperty(pPropScale);
		addProperty(pPropGroup);
	}
	if (typeid(*pModule.get()) == typeid(Mesh))
	{
		SmartPointer<Mesh> pMesh = pModule.SmartPointerCast<Mesh>();
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
		SmartPointer<RasterCamera> pCamera = pModule.SmartPointerCast<RasterCamera>();;
		QtProperty*	pCameraProperty = groupManager->addProperty(tr("RasterCamera"));
		//
		QtProperty* pProperty = doubleManager->addProperty(tr("FOV"));
		doubleManager->setValue(pProperty,pCamera->m_fFovy);
		pCameraProperty->addSubProperty(pProperty);
		//
		pProperty = doubleManager->addProperty( tr("Aspect"));
		doubleManager->setValue(pProperty,pCamera->m_fAspect);
		pCameraProperty->addSubProperty(pProperty);
		//
		pProperty = doubleManager->addProperty(tr("Near Plane"));
		doubleManager->setValue(pProperty,pCamera->m_fNear);
		pCameraProperty->addSubProperty(pProperty);
		//
		pProperty = doubleManager->addProperty(tr("Far Plane"));
		doubleManager->setValue(pProperty,pCamera->m_fFar);
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
		SmartPointer<PointLight> pPointLight = pModule.SmartPointerCast<PointLight>();
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
		SmartPointer<DirectionalLight> pDirLight = pModule.SmartPointerCast<DirectionalLight>();
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
		SmartPointer<Sphere3D> pSphere = pModule.SmartPointerCast<Sphere3D>();
		QtProperty* pSphereGroup = groupManager->addProperty(tr("Sphere"));
		addProperty(pSphereGroup);

		QtVariantProperty* pProperty = variantManager->addProperty(QVariant::Double, tr("Radius"));
		pSphereGroup->addSubProperty(pProperty);
		pProperty->setValue(pSphere->m_fRadius);
		AddEditorProperty(pSphere.get(), "RADIUS", pProperty);

		pProperty = variantManager->addProperty(QVariant::Int, tr("Subdivide"));
		pSphereGroup->addSubProperty(pProperty);
		pProperty->setValue(pSphere->m_nSubdivide);
		AddEditorProperty(pSphere.get(), "SUBDIVIDE", pProperty);
	}
	if (typeid(*pModule.get()) == typeid(SkeletonModule))
	{
		SmartPointer<SkeletonModule> pSkeleton = pModule.SmartPointerCast<SkeletonModule>();
		QtProperty* pSkeletonGroup = groupManager->addProperty(tr("Skeleton"));
		addProperty(pSkeletonGroup);
		std::string pSkeletonRef = "";
		if (pSkeleton->GetSkeletonRes() != nullptr)
		{
			pSkeletonRef = pSkeleton->GetSkeletonRes()->GetRefPath();
		}
 		QtProperty * pFilePath = filePathManager->addProperty(tr("SkeletonPath"));
		filePathManager->setValue(pFilePath, pSkeletonRef.c_str());
		filePathManager->setFilter(pFilePath, "MeshFile files (*.Skeleton)");
		pSkeletonGroup->addSubProperty(pFilePath);



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

void ZG::WorldObjPropertyBrowser::valueChanged(QtProperty *pProp, double f)
{
	SetDoubleStep(pProp);

	if (m_PropertyMap.find(pProp) == std::end(m_PropertyMap))
	{
		return;
	}
	float fValue = f;
	m_PropertyMap[pProp]->SetProperty(&fValue);
}

void ZG::WorldObjPropertyBrowser::SetDoubleStep(QtProperty* pProperty)
{
	float fValue = doubleManager->value(pProperty);
	doubleManager->setDecimals(pProperty, 4);
	if (fabs(fValue) <= 0.01f)
	{
		doubleManager->setSingleStep(pProperty, 0.01f);
		
	}
	else 	if (fabs(fValue) <= 0.1f)
	{
		doubleManager->setSingleStep(pProperty, fabs(fValue) / 5.0f);

	}
	else
	{
		doubleManager->setSingleStep(pProperty, fabs(fValue) / 10.0f);
	}
}

void WorldObjPropertyBrowser::AddEditorProperty(SmartPointer<ModuleBase> pModule, std::string propName, QtProperty* pProp)
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

void WorldObjPropertyBrowser::UpdateProperty()
{
	for each (std::pair<QtProperty*, EditorModuleProperty*> p in m_PropertyMap)
	{
		QtVariantProperty* pProperty = dynamic_cast<QtVariantProperty*>(p.first);
		if (pProperty != nullptr)
		{
			switch (pProperty->valueType())
			{
				case QVariant::Double:
				{
					float fValue = 0.0f;
					p.second->GetValue(&fValue);
					pProperty->setValue(fValue);

				}
				break;
				case QVariant::Int:
				{
					int nValue = 0;
					p.second->GetValue(&nValue);
					pProperty->setValue(nValue);
				}
				break;
				default:
				{
				}
				break;
			}
		}
		QtProperty* pCMProperty = p.first;
		if (pCMProperty->propertyManager() == doubleManager)
		{
			float fValue = 0.0f;
			p.second->GetValue(&fValue);
			doubleManager->setValue(pCMProperty, fValue);
		}
		
	}
}

