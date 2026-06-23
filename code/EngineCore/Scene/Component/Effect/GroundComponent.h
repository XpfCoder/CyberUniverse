#ifndef CYBER_GROUNDCONPONENT
#define CYBER_GROUNDCONPONENT
#endif // !CYBER_SkyComponent


#include "../../../Core/Engine/Component.h"
namespace EngineCore
{

	class GroundComponent : public IComponent
	{
	public:
		GroundComponent(void** parameter);
		GroundComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	public:
		virtual void buildMesh() override;
		virtual void createVertexLayout(const ComPtr<ID3DBlob>& blob) override;
		virtual void bindPipeState() override;
		virtual void draw() override;
		virtual void drawShadowMap() override;
	};
}