#include "SkyComponent.h"
#include "../Common/VertexType.h"
#include "../Common/RenderStates.h"
#include "../Common/Geometry.h"
#include "../Camera/CameraManager.h"
namespace EngineCore
{
	SkyComponent::SkyComponent(void** parameter) : IComponent(parameter)
	{
		setComponetType("SkyComponent");

		buildMesh();

		m_pd3dImmediateContext->RSSetState(RenderStates::RSNoCull.Get());
		m_pd3dImmediateContext->OMSetDepthStencilState(RenderStates::DSSLessEqual.Get(), 0);

		setVsShader("builtin\\Shader\\SkyBoxComponentVS.cso");
		setPsShader("builtin\\Shader\\SkyBoxComponentPS.cso");
		setTexture("builtin\\Texture\\SkyBox\\desertcube1024.dds");
		setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f)
		));


	}

	SkyComponent::SkyComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext) : IComponent(pd3dDevice, pd3dImmediateContext)
	{
		setComponetType("SkyComponent");

		buildMesh();

		setVsShader("builtin\\Shader\\SkyBoxComponentVS.cso");
		setPsShader("builtin\\Shader\\SkyBoxComponentPS.cso");
		setTexture("builtin\\Texture\\SkyBox\\desertcube1024.dds");
		setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f)
		));

		D3D11_BUFFER_DESC cbd;
		ZeroMemory(&cbd, sizeof(cbd));
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.ByteWidth = sizeof(CBChangesEveryFrame);
		m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_CBFrame.GetAddressOf());
	}

	void SkyComponent::buildMesh()
	{
		m_pVertexBuffer.Reset();
		m_pIndexBuffer.Reset();


		auto sphere = Geometry::CreateSphere<Geometry::VertexPos>(1000);

		// 顶点缓冲区创建
		D3D11_BUFFER_DESC vbd;
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = sizeof(XMFLOAT3) * (UINT)sphere.vertexVec.size();
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;
		vbd.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = sphere.vertexVec.data();

		m_pd3dDevice->CreateBuffer(&vbd, &InitData, &m_pVertexBuffer);


		// 索引缓冲区创建
		m_indexCount = (UINT)sphere.indexVec.size();

		D3D11_BUFFER_DESC ibd;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = sizeof(DWORD) * m_indexCount;
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.StructureByteStride = 0;
		ibd.MiscFlags = 0;
		InitData.pSysMem = sphere.indexVec.data();
		m_pd3dDevice->CreateBuffer(&ibd, &InitData, &m_pIndexBuffer);

	}

	void SkyComponent::createVertexLayout(const ComPtr<ID3DBlob>& blob)
	{
		m_pd3dDevice->CreateInputLayout(Geometry::VertexPos::inputLayout, 1, blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout.GetAddressOf());
	}

	void SkyComponent::bindPipeState()
	{
		UINT stride = sizeof(Geometry::VertexPos);
		UINT offset = 0;
		m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
		m_pd3dImmediateContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout.Get());
		m_pd3dImmediateContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
		m_pd3dImmediateContext->GSSetShader(m_pGeometryShader.Get(), nullptr, 0);
		m_pd3dImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);

		m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pTexture.GetAddressOf());

		m_pd3dImmediateContext->VSSetConstantBuffers(0, 1, m_CBFrame.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(0, 1, m_CBFrame.GetAddressOf());
		m_pd3dImmediateContext->VSSetConstantBuffers(4, 1, m_pWorldMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(4, 1, m_pWorldMatrixCB.GetAddressOf());


		m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		m_pd3dImmediateContext->GSSetShader(nullptr, nullptr, 0);
		m_pd3dImmediateContext->RSSetState(RenderStates::RSNoCull.Get());
		//m_pd3dImmediateContext->RSSetState(RenderStates::RSWireframe.Get());

		m_pd3dImmediateContext->PSSetSamplers(0, 1, RenderStates::SSLinearWrap.GetAddressOf());
		m_pd3dImmediateContext->OMSetDepthStencilState(RenderStates::DSSLessEqual.Get(), 0);
		m_pd3dImmediateContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
	}

	void SkyComponent::draw()
	{
		bindPipeState();

		XMMATRIX V = CameraManager::getInstance().getViewMatrix();
		XMMATRIX P = CameraManager::getInstance().getProjMatrix();
		V.r[3] = g_XMIdentityR3;
	
		CBChangesEveryFrame cBChangesEveryFrame;
		cBChangesEveryFrame.worldViewProj = XMMatrixTranspose(V*P);


		if (m_CBFrame)
		{
			D3D11_MAPPED_SUBRESOURCE mappedData;
			m_pd3dImmediateContext->Map(m_CBFrame.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
			memcpy_s(mappedData.pData, sizeof(CBChangesEveryFrame), &cBChangesEveryFrame, sizeof(CBChangesEveryFrame));
			m_pd3dImmediateContext->Unmap(m_CBFrame.Get(), 0);
		}

		
		m_pd3dImmediateContext->DrawIndexed(m_indexCount, 0, 0);
	}

	void SkyComponent::drawShadowMap()
	{
		UINT stride = sizeof(Geometry::VertexPos);
		UINT offset = 0;
		m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
		m_pd3dImmediateContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pTexture.GetAddressOf());
		m_pd3dImmediateContext->PSSetSamplers(0, 1, RenderStates::SSLinearWrap.GetAddressOf()); 

		m_pd3dImmediateContext->VSSetConstantBuffers(3, 1, m_pWorldMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(3, 1, m_pWorldMatrixCB.GetAddressOf());

		m_pd3dImmediateContext->DrawIndexed(m_indexCount, 0, 0);
	}
}
