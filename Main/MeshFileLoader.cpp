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
	int nLength = 4;

	//index data
	//index desc
	int indexDesc;
	fread((void*)&indexDesc, sizeof(int), 1, fp);
	nLength += 4;
	//index num
	unsigned int nIndexNum;
	fread((void*)&nIndexNum, sizeof(unsigned int), 1, fp);
	nLength += 4;
	res->m_IndexData.indexNum = nIndexNum;
	res->m_IndexData.indexDesc = (EnumIndexDesc)indexDesc;
	unsigned int nIndexStrip = 2;
	if (res->m_IndexData.indexDesc == EIndexInt)
	{
		nIndexStrip = 4;
	}
	unsigned int nIndexBuffLength = nIndexStrip * nIndexNum;
	res->m_IndexData.pData = (void*)new unsigned char[nIndexBuffLength];
	fread((void*)res->m_IndexData.pData, nIndexBuffLength, 1, fp);
	nLength += nIndexBuffLength;


	//vertex data
	unsigned int nVDescNum;
	fread((void*)&nVDescNum, sizeof(unsigned int), 1, fp);
	nLength += 4;
	for (int i = 0; i < nVDescNum; ++i)
	{
		VertexData::VertexDataDesc desc;
		int usedesc, typedesc, nOffset;
		fread((void*)&usedesc,sizeof(int),1,fp);
		fread((void*)&typedesc, sizeof(int), 1, fp);
		fread((void*)&nOffset, sizeof(int), 1, fp);
		nLength += 12;
		desc.usedesc = (EnumVertexUseDesc)usedesc;
		desc.typedesc = (EnumVertexTypeDesc)typedesc;
		desc.nOffset = nOffset;
		res->m_VertexData.vecDataDesc.push_back(desc);
	}
	unsigned int nSizeOfVB;
	fread((void*)&nSizeOfVB, sizeof(unsigned int), 1, fp);
	nLength += 4;
	res->m_VertexData.nNumVertex = nSizeOfVB / res->m_VertexData.GetVertexDataLength();
	//unsigned int nVBuffSize = nVertexNum * res->m_VertexData.GetVertexDataLength();
	res->m_VertexData.pData = (void*)new unsigned char[nSizeOfVB];
	fread(res->m_VertexData.pData, nSizeOfVB, 1, fp);
	nLength += nSizeOfVB;
	for (unsigned int i = 0; i < res->m_VertexData.nNumVertex; ++i)
	{
		Vector3 pos = *((Vector3*)res->m_VertexData.GetElementData(1,i));
		//std::cout << "normal:" << pos.m_fx << " " << pos.m_fy << " "<<pos.m_fz << std::endl;
	}
	pMeshAsset->AddResource(path, res);
	return pMeshAsset;
}
