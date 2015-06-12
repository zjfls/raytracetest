#pragma once
#include "Orientation.h"
#include "ModuleBase.h"
#include "Matrix33.h"
#include "Matrix44.h"

/////////////////////////////////////////////////
namespace ZG
{
	class WORLD_API Transform :public ModuleBase
	{
	public:

		~Transform();

		virtual void Update();
		Vector3	GetRight();
		Vector3 GetForward();
		Vector3	GetUp();
		void NotifyNeedTransform();
		bool m_bThisFrameUpdated;


		void SetTranslate(float fX, float fY, float fZ);
		void SetTranslate(const Vector3& vecIn);
		void SetOrientation(float fX, float fY, float fZ);
		void SetScale(float fx, float fY, float fZ);


		Vector3 GetLocalTranslate() const { return m_vecTranslate; };
		Vector3 GetWorldTranslate()const;// { return m_vecTranslate; };
		void	SetWorldTranslate(const Vector3& vecTrans);
		void	SetWorldTransform(const Matrix44& mat);
		Vector3 GetScale()const{ return m_vecScale; };
		Orientation GetOrientation()const{ return m_Orientation; };



		Matrix44 GetWorldMatrix() const;
		//only update self transform
		//Matrix44 UpdateSelfTransform() const;
		virtual SmartPointer<ModuleBase> Clone();

		////////////////////////////////////////////////


	private:
		Matrix44	m_TransformMatrixLocal;
		Matrix44	m_TransformMatrixWorld;
		bool m_bDirt;

		Point3D m_vecTranslate;
		Orientation m_Orientation;
		Vector3 m_vecScale;

	private:
		Transform();
		friend class IWorldObj;
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




