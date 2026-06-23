#ifndef CYBER_SKYCONPONENT
#define CYBER_SKYCONPONENT
#endif // !CYBER_SkyComponent


#include "../../../Core/Engine/Component.h"
namespace EngineCore
{
	struct CBChangesEveryFrame
	{
		DirectX::XMMATRIX worldViewProj;
	};

	class SkyComponent : public IComponent
	{
	public:
		SkyComponent(void** parameter);
		SkyComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	public:
		virtual void buildMesh() override;
		virtual void createVertexLayout(const ComPtr<ID3DBlob>& blob) override;
		virtual void bindPipeState() override;
		virtual void draw() override;
		virtual void drawShadowMap() override;
	private:
		ComPtr<ID3D11Buffer> m_CBFrame{ nullptr };        // 每帧绘制的常量缓冲区
	};
}