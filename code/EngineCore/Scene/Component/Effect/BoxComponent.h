#ifndef CYBER_BOXCOMPONENT
#define CYBER_BOXCOMPONENT
#endif // !CYBER_BOXCOMPONENT


#include "../../../Core/Engine/Component.h"
namespace EngineCore
{
	class BoxComponent : public IComponent
	{
	public:
		BoxComponent(void** parameter);
		BoxComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	public:
		virtual void buildMesh() override;
		virtual void createVertexLayout(const ComPtr<ID3DBlob>& blob) override;
		virtual void bindPipeState() override;
		virtual void draw() override;
		virtual void drawShadowMap() override;
	};
}