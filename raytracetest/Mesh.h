#pragma once




class MeshResource;
class Mesh:public IRenderable
{
public:
	Mesh();
	virtual ~Mesh();
	//std::vector<int> m_IndexBuffer;



	
	shared_ptr<MeshResource> m_pResource;
};

