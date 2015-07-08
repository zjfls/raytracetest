#pragma once
#include "Orientation.h"
#include "ModuleBase.h"
#include "Matrix33.h"
#include "Matrix44.h"

/////////////////////////////////////////////////
namespace ZG
{
	struct MAIN_API stTransformData
	{
		Point3D m_vecTranslate;
		Vector3 m_vecRotation;
		Vector3 m_vecScale;
		stTransformData()
		{
			m_vecScale = Vector3::ONE;
		}
		stTransformData(const stTransformData& tData)
		{
			m_vecTranslate = tData.m_vecTranslate;
			m_vecRotation = tData.m_vecRotation;
			m_vecScale = tData.m_vecScale;
		}
		stTransformData& operator=(const stTransformData& data);
		stTransformData operator+(const stTransformData& data);
		stTransformData operator*(const float fValue);
	};
	class MAIN_API Transform :public ModuleBase
	{
	public:

		~Transform();

		virtual void OnUpdate();
		Vector3	GetRight();
		Vector3 GetForward();
		Vector3	GetUp();
		void NotifyNeedTransform();
		


		void SetTranslate(float fX, float fY, float fZ);
		void SetTranslate(const Vector3& vecIn);
		void SetOrientation(float fX, float fY, float fZ);
		void SetScale(float fx, float fY, float fZ);


		
		Vector3 GetWorldTranslate();// { return m_vecTranslate; };
		void	SetWorldTranslate(const Vector3& vecTrans);
		void	SetWorldTransform(const Matrix44& mat);
		Vector3 GetLocalTranslate() const { return m_TransformData.m_vecTranslate; };
		Vector3 GetScale()const{ return m_TransformData.m_vecScale; };
		Vector3 GetRotation()const{ return m_TransformData.m_vecRotation; };



		Matrix44 GetWorldMatrix() const;
		Matrix44 GetLocalMatrix() const;
		//only update self transform
		//Matrix44 UpdateSelfTransform() const;
		virtual SmartPointer<ModuleBase> Clone();
		bool m_bThisFrameUpdated;
		////////////////////////////////////////////////
	private:
		void SetDirty(bool bDirt)
		{
			m_bDirt = bDirt;
		}
		

	private:
		Matrix44	m_TransformMatrixLocal;
		Matrix44	m_TransformMatrixWorld;
		bool m_bDirt;

		//Point3D m_vecTranslate;
		//Orientation m_Orientation;
		//Vector3 m_vecScale;
		

	private:
		Transform();
		friend class IWorldObj;
		private:
		stTransformData m_TransformData;
		friend class SkeletonModule;
	};


}


//class TransformCreator :public IModuleCreator
//{
//public:
//	TransformCreator();
//	virtual ~TransformCreator();
//
//
//	virtual ModuleBase* CreateModule();
//};




