#include "Component.h"
#include "Node.h"
#include "../../Asset/AssetManager.h"

namespace EngineCore
{
	RTTR_REGISTRATION
	{
		rttr::registration::class_<IComponent>("EngineCore::IComponent")
		;
	}


	size_t IComponent::getAddress()
	{
		return (size_t)this;
	}
	IComponent::IComponent(void** parameter)
	{
		m_pd3dDevice = (ID3D11Device*)parameter[0];
		m_pd3dImmediateContext = (ID3D11DeviceContext*)parameter[1];

		D3D11_BUFFER_DESC cbd;
		ZeroMemory(&cbd, sizeof(cbd));
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.ByteWidth = sizeof(WorldMatrix);
		m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pWorldMatrixCB.GetAddressOf());


		cbd.ByteWidth = sizeof(Material);
		m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pMaterialCB.GetAddressOf());


		cbd.ByteWidth = sizeof(UseTexOrColor);
		m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pUseColorCB.GetAddressOf());

		//generate uui
		GUID guid;
		CoCreateGuid(&guid);
		const UINT bufferLength = 256;
		char* guidStr = new char[bufferLength];
		_snprintf_s(guidStr, bufferLength, bufferLength - 1,
			"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2],
			guid.Data4[3], guid.Data4[4], guid.Data4[5],
			guid.Data4[6], guid.Data4[7]);
		m_uuid = guidStr;


		setMaterial(COMMON_MAT);
	}

	IComponent::IComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext) :
		m_pd3dDevice(pd3dDevice), m_pd3dImmediateContext(pd3dImmediateContext)
	{
		D3D11_BUFFER_DESC cbd;
		ZeroMemory(&cbd, sizeof(cbd));
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.ByteWidth = sizeof(WorldMatrix);
		m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pWorldMatrixCB.GetAddressOf());


		cbd.ByteWidth = sizeof(Material);
		m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pMaterialCB.GetAddressOf());


		cbd.ByteWidth = sizeof(UseTexOrColor);
		m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pUseColorCB.GetAddressOf());

		//generate uui
		GUID guid;
		CoCreateGuid(&guid);
		const UINT bufferLength = 256;
		char* guidStr = new char[bufferLength];
		_snprintf_s(guidStr, bufferLength, bufferLength - 1,
			"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2],
			guid.Data4[3], guid.Data4[4], guid.Data4[5],
			guid.Data4[6], guid.Data4[7]);
		m_uuid = guidStr;



		setMaterial(COMMON_MAT);
	}


	IComponent::~IComponent()
	{
		m_pWorldMatrixCB.Reset();
		m_pVertexShader.Reset();
		m_pPixelShader.Reset();
		m_pVertexLayout.Reset();
		m_pTexture.Reset();
		m_pMaterialCB.Reset();
		m_pUseColorCB.Reset();
	}

	void IComponent::setVsShader(const std::string& vsShader)
	{
		m_vsShader = vsShader;
		m_pVertexShader.Reset();

		ComPtr<ID3DBlob> blob;

		m_pVertexShader = AssetManager::getInstance().loadVsShaderAsset(vsShader, blob);
		if (m_pVertexShader)
			createVertexLayout(blob);

		blob.Reset();


	}

	void IComponent::setGsShader(const std::string& gsShader)
	{
		m_gsShader = gsShader;
		m_pGeometryShader.Reset();

		m_pGeometryShader = AssetManager::getInstance().loadGsShaderAsset(gsShader);
	}

	void IComponent::setPsShader(const std::string& psShader)
	{
		m_psShader = psShader;
		m_pPixelShader.Reset();

		m_pPixelShader = AssetManager::getInstance().loadPsShaderAsset(psShader);
	}

	void IComponent::setTexture(const std::string& texture)
	{
		m_texture = texture;
		m_pTexture.Reset();

		m_pTexture = AssetManager::getInstance().loadTextureAsset(texture);

	}

	void IComponent::setTexture(const std::vector<std::wstring>& TextureList)
	{

		m_pTexture = AssetManager::getInstance().loadTextureArrayAsset(TextureList);

	}

	void IComponent::setMaterial(const Material& material)
	{
		m_material = material;

		if (m_pMaterialCB)
		{
			D3D11_MAPPED_SUBRESOURCE mappedData;
			m_pd3dImmediateContext->Map(m_pMaterialCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
			memcpy_s(mappedData.pData, sizeof(Material), &m_material, sizeof(Material));
			m_pd3dImmediateContext->Unmap(m_pMaterialCB.Get(), 0);
		}
	}

	XMMATRIX XM_CALLCONV InverseTranspose(DirectX::FXMMATRIX M)
	{
		using namespace DirectX;

		XMMATRIX A = M;
		A.r[3] = g_XMIdentityR3;

		return XMMatrixTranspose(XMMatrixInverse(nullptr, A));
	}

	void IComponent::onTransformChanged()
	{
		WorldMatrix worldMatrix;
		worldMatrix.g_world = XMMatrixTranspose(m_transform.getWorldMatrix());
		worldMatrix.g_worldInvTranspose = InverseTranspose(m_transform.getWorldMatrix());

		if (m_pWorldMatrixCB)
		{
			D3D11_MAPPED_SUBRESOURCE mappedData;
			m_pd3dImmediateContext->Map(m_pWorldMatrixCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
			memcpy_s(mappedData.pData, sizeof(WorldMatrix), &worldMatrix, sizeof(WorldMatrix));
			m_pd3dImmediateContext->Unmap(m_pWorldMatrixCB.Get(), 0);
		}
	}

		void IComponent::setUseTexOrColor(bool isUseTex, const XMFLOAT4& color)
	{
		if (m_pUseColorCB)
		{
			UseTexOrColor useTexOrColor;
			useTexOrColor.isUseTex = isUseTex;
			useTexOrColor.texColor = color;

			if (m_pUseColorCB)
			{
				D3D11_MAPPED_SUBRESOURCE mappedData;
				m_pd3dImmediateContext->Map(m_pUseColorCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
				memcpy_s(mappedData.pData, sizeof(UseTexOrColor), &useTexOrColor, sizeof(UseTexOrColor));
				m_pd3dImmediateContext->Unmap(m_pUseColorCB.Get(), 0);
			}
		}
	}

	void IComponent::applyChanges()
	{
		onTransformChanged();

		if (m_pMaterialCB)
		{
			D3D11_MAPPED_SUBRESOURCE mappedData;
			m_pd3dImmediateContext->Map(m_pMaterialCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
			memcpy_s(mappedData.pData, sizeof(Material), &m_material, sizeof(Material));
			m_pd3dImmediateContext->Unmap(m_pMaterialCB.Get(), 0);
		}

		if (!m_texture.empty() && !m_pTexture)
		{
			m_pTexture = AssetManager::getInstance().loadTextureAsset(m_texture);
		}
		if (m_pUseColorCB)
		{
			UseTexOrColor useTexOrColor;
			useTexOrColor.isUseTex = m_texture.empty() ? 0.0f : 1.0f;
			useTexOrColor.texColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

			D3D11_MAPPED_SUBRESOURCE mappedData;
			m_pd3dImmediateContext->Map(m_pUseColorCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
			memcpy_s(mappedData.pData, sizeof(UseTexOrColor), &useTexOrColor, sizeof(UseTexOrColor));
			m_pd3dImmediateContext->Unmap(m_pUseColorCB.Get(), 0);
		}
	}

}
