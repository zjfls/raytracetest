#pragma once




class MeshResource;
class Mesh:public IRenderable
{
public:
	Mesh();
	virtual ~Mesh();
	std::vector<int> m_IndexBuffer;



	
	MeshResource* m_pResource;
};

