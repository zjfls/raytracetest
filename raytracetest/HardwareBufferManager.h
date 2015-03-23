#pragma once


class IndexData;
class VertexData;
class HardwareIndexBuffer;
class HardwareVertexBuffer;
class HardwareBufferManager:public Singleton<HardwareBufferManager>
{
public:
	HardwareBufferManager();
	virtual ~HardwareBufferManager();




	std::map<IndexData*, HardwareIndexBuffer*> m_IndexDataMap;
	std::map<VertexData*, HardwareVertexBuffer*> m_VertexDataMap;
};

