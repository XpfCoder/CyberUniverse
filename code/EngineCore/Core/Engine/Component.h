#ifndef CYBER_COMPONENT
#define CYBER_COMPONENT

#include <DirectXMath.h>
#include <d3d11_1.h>
#include <DirectXCollision.h>
#include "../../Scene/Component/Common/Material.h"
#include "../../Scene/Component/Common/RenderStates.h"
#include "../../Scene/Component/Common/Transform.h"
#include <vector>
#include <wrl\client.h>
#include <rttr/registration>
namespace EngineCore
{
	using namespace DirectX;
	using Microsoft::WRL::ComPtr;

	class Node;

	class __declspec(dllexport) IComponent
	{
	public:
		struct WorldMatrix
		{
			XMMATRIX g_world;
			XMMATRIX g_worldInvTranspose;
		};

		struct UseTexOrColor
		{
			XMFLOAT4 texColor;
			XMFLOAT3 padd;
			float isUseTex;
		};


	public:
		virtual size_t getAddress();
		IComponent() = default;
		IComponent(void** parameter);
		IComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
		virtual ~IComponent();
		virtual void buildMesh() = 0;
		virtual void createVertexLayout(const ComPtr<ID3DBlob>& blob) = 0;
		virtual void bindPipeState() = 0;
		virtual void draw() = 0;
		virtual void drawShadowMap() = 0;

		// Apply property changes to D3D11 resources
		virtual void applyChanges();

	public:
		virtual std::string getVsShader() { return m_vsShader; }
		virtual void setVsShader(const std::string& vsShader);

		virtual std::string getPsShader() { return m_psShader; }
		virtual void setPsShader(const std::string& psShader);

		virtual std::string getGsShader() { return m_gsShader; }
		virtual void setGsShader(const std::string& gsShader);

		virtual std::string getTexture() { return m_texture; }
		virtual void setTexture(const std::string& texture);
		virtual void setTexture(const std::vector<std::wstring>& TextureList);

		virtual Material getMaterial() { return m_material; }
		virtual void setMaterial(const Material& material);
	public:
		void onTransformChanged();
		virtual Transform getTransform() { return m_transform; }
		virtual void setTransform(const Transform& transform) { m_transform = transform; onTransformChanged(); }

		virtual XMFLOAT3 getScale() { return m_transform.getScale(); }
		virtual void setScale(float x, float y, float z) { setScale(XMFLOAT3(x, y, z)); }
		virtual void setScale(const XMFLOAT3& scale) { m_transform.setScale(scale); onTransformChanged(); }

		virtual XMFLOAT3 getRotation() { return m_transform.getRotation(); }
		virtual void setRotation(float x, float y, float z) { setRotation(XMFLOAT3(x, y, z)); }
		virtual void setRotation(const XMFLOAT3& rot) { m_transform.setRotation(rot); onTransformChanged(); }

		virtual XMFLOAT3 getPosition() { return m_transform.getPosition(); }
		virtual void setPosition(float x, float y, float z) { setPosition(XMFLOAT3(x, y, z)); }
		virtual void setPosition(const XMFLOAT3& pos) { m_transform.setPosition(pos); onTransformChanged(); }

		virtual BoundingBox getBoundingBox() { return m_boundingBox; };
		virtual void setBoundingBox(BoundingBox boundingBox) { m_boundingBox = boundingBox; };

		void setComponetType(const std::string componetType) { m_componetType = componetType; }
		virtual std::string getComponetType() { return m_componetType; }
		virtual std::string getUuId() { return m_uuid; }

		virtual UINT getTriangleCount() { return m_indexCount / 3; }
		void setUseTexOrColor(bool isUseTex, const XMFLOAT4& color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		virtual void setShadowMap(ID3D11ShaderResourceView* pSRV) { m_pShadowMapTexture = pSRV; }

		// Owner node
		void setOwnerNode(Node* node) { m_ownerNode = node; }
		Node* getOwnerNode() const { return m_ownerNode; }

	protected:
		ComPtr<ID3D11Device> m_pd3dDevice{ nullptr };
		ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext{ nullptr };

		ComPtr<ID3D11VertexShader> m_pVertexShader{ nullptr };
		ComPtr<ID3D11PixelShader> m_pPixelShader{ nullptr };
		ComPtr<ID3D11GeometryShader> m_pGeometryShader{ nullptr };
		ComPtr<ID3D11InputLayout> m_pVertexLayout{ nullptr };

		ComPtr<ID3D11ShaderResourceView> m_pTexture{ nullptr };
		ComPtr<ID3D11ShaderResourceView> m_pShadowMapTexture{ nullptr };

		ComPtr<ID3D11Buffer> m_pWorldMatrixCB{ nullptr };
		ComPtr<ID3D11Buffer> m_pMaterialCB{ nullptr };

		ComPtr<ID3D11Buffer> m_pVertexBuffer{ nullptr };
		ComPtr<ID3D11Buffer> m_pIndexBuffer{ nullptr };

		ComPtr<ID3D11Buffer> mPointSpritesBuffer{ nullptr };
		ComPtr<ID3D11Buffer> m_pUseColorCB{ nullptr };

		Node* m_ownerNode{ nullptr };
	protected:
		std::string m_vsShader;
		std::string m_gsShader;
		std::string m_psShader;
		std::string m_texture;
		Material m_material;
		Transform m_transform{ {1.0f, 1.0f, 1.0f},{0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 0.0f} };
		BoundingBox m_boundingBox;

		std::string m_uuid;
		std::string m_componetType;

		UINT m_indexCount = 0;
	};
}


#endif // !CYBER_COMPONENT