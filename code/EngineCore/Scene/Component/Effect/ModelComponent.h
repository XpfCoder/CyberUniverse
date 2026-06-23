#ifndef CYBER_ModelComponent
#define CYBER_ModelComponent
#endif // !CYBER_ModelComponent
#include "../../../Asset/Model.h"

#include "../../../Core/Engine/Component.h"
namespace EngineCore
{
	class ModelComponent : public IComponent
	{
	public:
		ModelComponent(void** parameter);
		ModelComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	public:
		virtual void buildMesh() override;
		virtual void createVertexLayout(const ComPtr<ID3DBlob>& blob) override;
		virtual void bindPipeState() override;
		virtual void draw() override;
		virtual void drawShadowMap() override;

		void SetModel(Model&& model);
		void SetModel(const Model& model);
	private:
		Model m_Model = {};												// Ä£ÐÍ
	};
}