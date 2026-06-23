#include "GroundComponent.h"
#include "../Common/VertexType.h"
#include "../Common/RenderStates.h"
#include "../Common/Geometry.h"
#include "../Camera/CameraManager.h"
namespace EngineCore
{
	GroundComponent::GroundComponent(void** parameter) : IComponent(parameter)
	{
		setComponetType("GroundComponent");

		buildMesh();

		m_pd3dImmediateContext->RSSetState(RenderStates::RSNoCull.Get());
		m_pd3dImmediateContext->OMSetDepthStencilState(RenderStates::DSSLessEqual.Get(), 0);

		setVsShader("builtin\\Shader\\BasicPrimitiveVS.cso");
		setPsShader("builtin\\Shader\\BasicPrimitivePS.cso");
		setTexture("builtin\\Texture\\Grass.dds");
		setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f)
		));


	}

	GroundComponent::GroundComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext) : IComponent(pd3dDevice, pd3dImmediateContext)
	{
		setComponetType("GroundComponent");

		buildMesh();


		setVsShader("builtin\\Shader\\BasicPrimitiveVS.cso");
		setPsShader("builtin\\Shader\\BasicPrimitivePS.cso");
		setTexture("builtin\\Texture\\Grass.dds");
		setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, -5.0f, 0.0f)
		));

	}

	void GroundComponent::buildMesh()
	{
		m_pVertexBuffer.Reset();
		m_pIndexBuffer.Reset();


		auto plane = Geometry::CreatePlane(XMFLOAT2(100.0f, 100.0f), XMFLOAT2(10.0f, 10.0f));

		// 顶点缓冲区创建
		D3D11_BUFFER_DESC vbd;
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = sizeof(Geometry::VertexPosNormalTex) * (UINT)plane.vertexVec.size();
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;
		vbd.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = plane.vertexVec.data();

		m_pd3dDevice->CreateBuffer(&vbd, &InitData, &m_pVertexBuffer);


		// 索引缓冲区创建
		m_indexCount = (UINT)plane.indexVec.size();

		D3D11_BUFFER_DESC ibd;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = sizeof(DWORD) * m_indexCount;
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.StructureByteStride = 0;
		ibd.MiscFlags = 0;
		InitData.pSysMem = plane.indexVec.data();
		m_pd3dDevice->CreateBuffer(&ibd, &InitData, &m_pIndexBuffer);

	}

	void GroundComponent::createVertexLayout(const ComPtr<ID3DBlob>& blob)
	{
		m_pd3dDevice->CreateInputLayout(Geometry::VertexPosNormalTex::inputLayout, 3, blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout.GetAddressOf());
	}

	void GroundComponent::bindPipeState()
	{
		UINT stride = sizeof(Geometry::VertexPosNormalTex);
		UINT offset = 0;
		m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
		m_pd3dImmediateContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout.Get());
		m_pd3dImmediateContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
		m_pd3dImmediateContext->GSSetShader(m_pGeometryShader.Get(), nullptr, 0);
		m_pd3dImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);

		m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pTexture.GetAddressOf());


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

	void GroundComponent::draw()
	{
		bindPipeState();
		
		m_pd3dImmediateContext->DrawIndexed(m_indexCount, 0, 0);
	}

	void GroundComponent::drawShadowMap()
	{
		UINT stride = sizeof(Geometry::VertexPosNormalTex);
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
