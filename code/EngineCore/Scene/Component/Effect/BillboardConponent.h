#ifndef CYBER_BILLBOARDCOMPONENT
#define CYBER_BILLBOARDCOMPONENT
#endif // !CYBER_BOXCOMPONENT


#include "../../../Core/Engine/Component.h"
namespace EngineCore
{
	class BillboardConponent : public IComponent
	{
	public:
		BillboardConponent(void** parameter);
		BillboardConponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	public:
		virtual void buildMesh() override;
		virtual void createVertexLayout(const ComPtr<ID3DBlob>& blob) override;
		virtual void bindPipeState() override;
		virtual void draw() override;
		virtual void drawShadowMap() override;
	};
}