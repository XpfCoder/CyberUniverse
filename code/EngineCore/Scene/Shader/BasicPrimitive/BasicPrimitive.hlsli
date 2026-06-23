#include "../CommonShader.hlsli"

struct VertexIn
{
	float3 posL : POSITION;
	float3 normalL : NORMAL;
	float2 texcoord : TEXCOORD;
};

struct VertexOut
{
	float4 posH : SV_POSITION;
	float3 posW : POSITION;
	float3 normalW: NORMAL;
	float2 texcoord: TEXCOORD;
	float4 ShadowPosH : TEXCOORD1;
};

cbuffer WorldMatrix : register(b4)
{
	matrix g_world;
	matrix g_worldInvTranspose;
}

cbuffer  MaterialCB : register(b5)
{
	Material g_material;
}

cbuffer UseTexOrColor : register(b6)
{
	float4 texColor;
	float3 padd;
	float isUseTex;
}