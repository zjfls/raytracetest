#include "stdafx.h"
#include "MeshFileLoader.h"
#include "MeshAsset.h"
#include "MeshResource.h"
#include "ResourceManager.h"
MeshFileLoader::MeshFileLoader()
{
}


MeshFileLoader::~MeshFileLoader()
{
}

IAsset* MeshFileLoader::Load(string path, void* pArg /*= nullptr*/)
{
	MeshAsset* pMeshAsset = new MeshAsset;
	pMeshAsset->m_strPath = path;
	shared_ptr<MeshResource> res = ResourceManager<MeshResource>::GetInstance()->CreateResource<MeshResource>(path);

	//
	FILE* fp;
	errno_t eOpen = fopen_s(&fp, path.c_str(), "rb");
	if (0 != eOpen)
	{
		std::cout << "open file:" << path.c_str() << std::endl;
		return nullptr;
	}
	unsigned int Version;
	fread((void*)&Version, sizeof(unsigned int), 1, fp);

	//index data
	//index desc
	int indexDesc;
	fread((void*)&indexDesc, sizeof(int), 1, fp);
	unsigned int nIndexNum;
	fread((void*)&nIndexNum, sizeof(unsigned int), 1, fp);
	res->m_IndexData.indexNum = nIndexNum;
	
	res->m_IndexData.indexDesc = (EnumIndexDesc)indexDesc;
	unsigned int nIndexStrip = 2;
	if (res->m_IndexData.indexDesc == EIndexInt)
	{
		nIndexStrip = 4;
	}
	//
	unsigned int nIndexBuffLength = nIndexStrip * nIndexNum;
	res->m_IndexData.pData = (void*)new unsigned char;
	fread((void*)res->m_IndexData.pData, nIndexBuffLength, 1, fp);



	//vertex data
	unsigned int nVDescNum;
	fread((void*)&nVDescNum, sizeof(unsigned int), 1, fp);
	for (int i = 0; i < nVDescNum; ++i)
	{
		VertexData::VertexDataDesc desc;
		int usedesc, typedesc, nOffset;
		fread((void*)&usedesc,sizeof(int),1,fp);
		fread((void*)&typedesc, sizeof(int), 1, fp);
		fread((void*)&nOffset, sizeof(int), 1, fp);
		desc.usedesc = (EnumVertexUseDesc)usedesc;
		desc.typedesc = (EnumVertexTypeDesc)typedesc;
		desc.nOffset = nOffset;
		res->m_VertexData.vecDataDesc.push_back(desc);
	}
	unsigned int nVertexNum;
	fread((void*)&nVertexNum, sizeof(unsigned int), 1, fp);
	res->m_VertexData.nNumVertex = nVertexNum;
	unsigned int nVBuffSize = nVertexNum * res->m_VertexData.GetVertexDataLength();
	res->m_VertexData.pData = (void*)new unsigned char[nVBuffSize];
	fread(res->m_VertexData.pData, nVBuffSize, 1, fp);

	pMeshAsset->AddResource(path, res);
	return pMeshAsset;
}
