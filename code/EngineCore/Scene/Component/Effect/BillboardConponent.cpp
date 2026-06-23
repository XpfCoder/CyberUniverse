#include "BillboardConponent.h"
#include "../Common/VertexType.h"
#include "../Common/RenderStates.h"
#include <vector>
#include <ctime>
namespace EngineCore
{
	BillboardConponent::BillboardConponent(void** parameter) : IComponent(parameter)
	{
		setComponetType("BillboardConponent");

		buildMesh();

		setVsShader("builtin\\Shader\\Billboard_VS.cso");
		setPsShader("builtin\\Shader\\Billboard_PS.cso");
		setGsShader("builtin\\Shader\\Billboard_GS.cso");
		setTexture(std::vector<std::wstring>{ L"..\\Texture\\tree0.dds",L"..\\Texture\\tree1.dds",L"..\\Texture\\tree2.dds",L"..\\Texture\\tree3.dds"});
		setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f)
		));
	}

	BillboardConponent::BillboardConponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext) : IComponent(pd3dDevice, pd3dImmediateContext)
	{
		setComponetType("BillboardConponent");

		buildMesh();

		setVsShader("builtin\\Shader\\Billboard_VS.cso");
		setPsShader("builtin\\Shader\\Billboard_PS.cso");
		setGsShader("builtin\\Shader\\Billboard_GS.cso");
		setTexture(std::vector<std::wstring>{ L"builtin\\Texture\\tree0.dds", L"builtin\\Texture\\tree1.dds", L"builtin\\Texture\\tree2.dds", L"builtin\\Texture\\tree3.dds"});
		setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f)
		));
	}

	void BillboardConponent::buildMesh()
	{
		m_pVertexBuffer.Reset();
		m_pIndexBuffer.Reset();
		m_indexCount = 16;
		srand((unsigned)time(nullptr));
		Geometry::VertexPosSize vertexes[16];
		float theta = 0.0f;
		for (int i = 0; i < m_indexCount; ++i)
		{
			// 取20-50的半径放置随机的树
			float radius = (float)(rand() % 31 + 20);
			float randomRad = rand() % 256 / 256.0f * XM_2PI / m_indexCount;
			vertexes[i].pos = XMFLOAT3(radius * cosf(theta + randomRad), 8.0f, radius * sinf(theta + randomRad));
			vertexes[i].size = XMFLOAT2(30.0f, 30.0f);
			theta += XM_2PI / m_indexCount;
		}

		// 设置顶点缓冲区描述
		D3D11_BUFFER_DESC vbd;
		ZeroMemory(&vbd, sizeof(vbd));
		vbd.Usage = D3D11_USAGE_IMMUTABLE;	// 数据不可修改
		vbd.ByteWidth = sizeof(vertexes);
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		// 新建顶点缓冲区
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = vertexes;
		m_pd3dDevice->CreateBuffer(&vbd, &InitData, mPointSpritesBuffer.GetAddressOf());




		//BoundingBox
		XMFLOAT3 vMin(-1.0f, -1.0f, -1.0f);
		XMFLOAT3 vMax(1.0f, 1.0f, 1.0f);
		BoundingBox aabb;
		BoundingBox::CreateFromPoints(aabb, XMLoadFloat3(&vMin), XMLoadFloat3(&vMax));
		setBoundingBox(aabb);
	}

	void BillboardConponent::createVertexLayout(const ComPtr<ID3DBlob>& blob)
	{
		m_pd3dDevice->CreateInputLayout(Geometry::VertexPosSize::inputLayout, 2, blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout.GetAddressOf());
	}

	void BillboardConponent::bindPipeState()
	{
		UINT stride = sizeof(Geometry::VertexPosSize);
		UINT offset = 0;
		m_pd3dImmediateContext->IASetVertexBuffers(0, 1, mPointSpritesBuffer.GetAddressOf(), &stride, &offset);
		m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

		m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout.Get());
		m_pd3dImmediateContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
		m_pd3dImmediateContext->GSSetShader(m_pGeometryShader.Get(), nullptr, 0);
		m_pd3dImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);

		m_pd3dImmediateContext->PSSetShaderResources(1, 1, m_pTexture.GetAddressOf());
		m_pd3dImmediateContext->PSSetSamplers(0, 1, RenderStates::SSLinearWrap.GetAddressOf());
		//m_pd3dImmediateContext->PSSetSamplers(1, 1, RenderStates::SSShadow.GetAddressOf());
		m_pd3dImmediateContext->OMSetDepthStencilState(nullptr, 0);
		m_pd3dImmediateContext->VSSetConstantBuffers(4, 1, m_pWorldMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(4, 1, m_pWorldMatrixCB.GetAddressOf());
		m_pd3dImmediateContext->VSSetConstantBuffers(5, 1, m_pMaterialCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(5, 1, m_pMaterialCB.GetAddressOf());
		m_pd3dImmediateContext->VSSetConstantBuffers(6, 1, m_pUseColorCB.GetAddressOf());
		m_pd3dImmediateContext->PSSetConstantBuffers(6, 1, m_pUseColorCB.GetAddressOf());
	}

	void BillboardConponent::draw()
	{
		bindPipeState();
		m_pd3dImmediateContext->Draw(16, 0);
	}

	void BillboardConponent::drawShadowMap()
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
