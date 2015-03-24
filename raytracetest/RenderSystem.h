#pragma once
struct stRenderViewInfo;
class IRender;
class RenderView;
class RenderPath;
class RasterRender;

class HardwareVertexShader;
class HardwareFragShader;
class VertexShaderDesc;
class FragShaderDesc;
class HardwareVertexBuffer;
class HardwareIndexBuffer;
class RenderSystem
{
public:
	virtual ~RenderSystem();
	IRender* GetDefaultRender() const;
	RenderView* GetDefaultRenderView() const;




	virtual bool InitRenderSystem(const stRenderViewInfo& viewInfo) = 0;
	virtual HardwareVertexShader* GetHardwareVertexShader(const VertexShaderDesc& vertexShaderDesc) = 0;
	virtual HardwareFragShader* GetHardwareFragShader(const FragShaderDesc& fragShaderDesc) = 0;
	virtual HardwareVertexBuffer* GetHardwareVertexBuffer(VertexData* pData) = 0;
	virtual HardwareIndexBuffer*	GetHardwareIndexBuffer(IndexData* pData) = 0;


private:


protected:
	virtual void	CreateDefaultRender(const RenderPath* pPath) = 0;
	void	InitRender(RasterRender* pRender);
	std::unordered_map<string, HardwareVertexShader*> m_mapHardwareVertexShader;
	std::unordered_map<string, HardwareFragShader*> m_mapHardwareFragShader;
	std::unordered_map<IndexData*, HardwareIndexBuffer*> m_IndexDataMap;
	std::unordered_map<VertexData*, HardwareVertexBuffer*> m_VertexDataMap;
	IRender* m_pDefaultRender;
	RenderView* m_pDefaultRenderView;
	RenderSystem();
	friend class RenderManager;
};

