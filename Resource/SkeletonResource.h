#pragma once
#include "IResource.h"
#include "Singleton.h"
#include "ResourceManager.h"
#include "Vector3.h"
#include "Matrix44.h"
namespace ZG
{
	class RESOURCE_API Bone
	{
	public:
		Vector3 t;
		Vector3 r;
		Vector3 s;
		void UpdateMatrix(Matrix44 parentMat);
		string m_strName;
		Matrix44 m_SkeletonMatrix;
		Matrix44 m_MatrixInverse;
		unsigned int		nIndex;
		std::vector<Bone*> vecChild;
		int GetBoneIndexByName(string name);
	};
	class RESOURCE_API SkeletonResource :
		public IResource
	{
	public:
		SkeletonResource();
		~SkeletonResource();

		void UpdateMatrix();
		Bone* m_pRoot;
		friend class ResourceManager < SkeletonResource > ;
		std::map<int, Bone*> m_mapBone;//index to bone;
		unsigned int m_nBoneNum;
	};

	RESOURCE_TEMPLATE template  class RESOURCE_API Singleton < ResourceManager<SkeletonResource> > ;
}