#include "SkyBoxCommonShader.hlsli"

VertexPosHLOut VS(VertexPosLIn vIn)
{
	VertexPosHLOut vOut;

	// 设置z = w使得z/w = 1(天空盒保持在远平面)
	//float4 posW = mul(float4(vIn.posL, 1.0f), g_world);
	//float4 posV = mul(posW, g_view);
	//float4 posH = mul(posV, g_proj);
	float4 posH = mul(float4(vIn.posL, 1.0f), g_WorldViewProj);
	vOut.posH = posH.xyww;
	vOut.posL = vIn.posL;
	return vOut;
}
